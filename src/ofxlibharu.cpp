#include "ofxlibharu.h"

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data) {
	printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no, (HPDF_UINT)detail_no);
	
	ofxLibharuError libhErrors;
	puts(ofToString(libhErrors.getErrorInfo(error_no)).c_str());
	puts("--");
	//check https://github.com/libharu/libharu/wiki/Error-handling#wiki-List_of_error_codes for error codes
}

ofxLibharu::ofxLibharu() {
	setDPI(300);
	setPageSize(A4);
}

ofxLibharu::~ofxLibharu() {
	HPDF_Free(pdf);
}

void ofxLibharu::setup(PAGE_SIZE size, ORIENTATION o) {
	pdf = HPDF_New (error_handler, NULL);
	setCmykBackground(0, 0, 0, 1);
	setCmykForeground(0, 0, 0, 1);
	newPage();
	setOrientation(o);
	setPageSize(size);
}

bool hasDPI = false;

void ofxLibharu::updatePage() {
	if(page) {
		float r =  72.f / 25.4;
		HPDF_Page_SetWidth(page, pageSize.x*r);
		HPDF_Page_SetHeight(page, pageSize.y*r);
		if(!hasDPI) {
			HPDF_Page_GSave (page);
			HPDF_Page_Concat (page, 72.0f / dpi, 0, 0, 72.0f / dpi, 0, 0);
			hasDPI = true;
		}
	}
}

void ofxLibharu::setPageSize(PAGE_SIZE size) {
	switch(size) {
	case A3:
		setPageSize(297, 420);
		break;
	case A4:
		setPageSize(210, 297);
		break;
	case A5:
		setPageSize(148, 210);
		break;
	case US_LETTER:
		setPageSize(215.9, 279.4);
		break;
	default:
		setPageSize(210, 297);
		break;
	}
	setOrientation(orientation);
}

void ofxLibharu::setPageSize(PAGE_SIZE size, ORIENTATION o) {
	setPageSize(size);
	setOrientation(o);
}

void ofxLibharu::setPageSize(float x, float y) {
	pageSize.set(x, y);
	updatePage();
}

void ofxLibharu::setOrientation(ORIENTATION o) {
	orientation = o;
	if(orientation == PORTRAIT) {
		if(pageSize.x > pageSize.y)
			pageSize.set(pageSize.y, pageSize.x);
	} else if(orientation == LANDSCAPE) {
		if(pageSize.y > pageSize.x) {
			pageSize.set(pageSize.y, pageSize.x);
		}
	}
	setPageSize(pageSize.x, pageSize.y);
}

void ofxLibharu::setDPI(int d) {
	if(dpi == d)
		return;
	//revert old DPI convertion
	if(page) {
		HPDF_Page_GRestore (page);
	}
	dpi = d;
	float r = dpi / 25.4;
	pixelRatio.set(r, r);
	hasDPI = false;
	updatePage();
}

void ofxLibharu::newPage(PAGE_SIZE size, ORIENTATION o) {
	newPage();
	setPageSize(size);
	setOrientation(o);
}
void ofxLibharu::newPage(float w, float h) {
	setPageSize(w, h);
	newPage();
}

void ofxLibharu::newPage() {
	page = HPDF_AddPage(pdf);
}

void ofxLibharu::save(string path, bool inDataFolder) {
	if(inDataFolder)
		path = ofToDataPath(path, true);
	lastFileSaved = path;
	HPDF_SaveToFile(pdf, path.c_str());
}

void ofxLibharu::openLastSave()
{
	#ifdef TARGET_LINUX
		string com = "xdg-open "+lastFileSaved;
		system(com.c_str());
	#else
		ofLogError() << "SORRY OPEN LAST SAVE IS ONLY IMPLEMENTED ON LINUX";
	#endif
}

float ofxLibharu::convertDistance(float f){
	return f * pixelRatio.x;
}

float ofxLibharu::convertX(float x) {
	return x * pixelRatio.x;
}

float ofxLibharu::convertY(float y) {
	return (pageSize.y - y) * pixelRatio.y;
}

void ofxLibharu::setCmykBackground(float c, float m, float y, float k)
{
	HPDF_Page_SetCMYKFill(page, c, m, y, k);
	HPDF_Page_Fill(page);
}

void ofxLibharu::setCmykForeground(float c, float m, float y, float k)
{
	HPDF_Page_SetCMYKStroke(page, c, m, y, k);
	HPDF_Page_Stroke(page);

}

void ofxLibharu::disableBackground()
{
	HPDF_Page_Eofill(page);
}

void ofxLibharu::disableForeground()
{
	HPDF_Page_EofillStroke(page);
}

/*
void RGBToCMYK(int R, int G, int B, int &C, int &M, int &Y, int &K)
{
    C = 1 - (R / 255);
    M = 1 - (G / 255);
    Y = 1 - (B / 255);
    int TempK = 1;
    if (C < TempK) TempK = C;
    if (M < TempK) TempK = M;
    if (Y < TempK) TempK = Y;
    if (TempK == 1)
    {
        C = M = Y = 0;
    }
    else
    {
        C = (C - TempK) / (1 - TempK);
        M = (M - TempK) / (1 - TempK);
        Y = (Y - TempK) / (1 - TempK);
    }
    K = TempK;
}
*/
