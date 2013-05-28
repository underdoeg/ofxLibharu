#include "ofxlibharu.h"

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data) {

	ofxLibharuError libhErrors;
	string error = libhErrors.getErrorInfo(error_no);
	if(error!="") ofLogError() << libhErrors.getErrorInfo(error_no);
	else printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no, (HPDF_UINT)detail_no);
	//check https://github.com/libharu/libharu/wiki/Error-handling#wiki-List_of_error_codes for error codes
}

ofxLibharu::ofxLibharu() {
	setDPI(300);
	setPageSize(A4);
}

ofxLibharu::~ofxLibharu() {
	HPDF_Free(pdf);
}

//Document Handling ------------------------------------------------------------------------------

void ofxLibharu::setup(PAGE_SIZE size, ORIENTATION o) {
	pdf = HPDF_New (error_handler, NULL);
	setCmykBackground(0, 0, 0, 1);
	setCmykForeground(0, 0, 0, 1);
	newPage();
	setOrientation(o);
	setPageSize(size);

	//font default values
	setFont("Times-Roman");
	setFontSize(16);
	setTextAlignment(ALIGN_LEFT);
	setCharSpacing(0);
	setWordSpacing(0);
	setTextLeading(0);

	//graphics default values
	setFillType(OF_OUTLINE);
	setStrokeColor(0,0,0);
	setFillColor(150,150,150);
	setLineWidth(1);
}

void ofxLibharu::save(string path, bool inDataFolder) {
	if(inDataFolder)
		path = ofToDataPath(path, true);
	lastFileSaved = path;
	HPDF_SaveToFile(pdf, path.c_str());
}

void ofxLibharu::openLastSave() {
#ifdef TARGET_LINUX
	string com = "xdg-open "+lastFileSaved;
	system(com.c_str());
#else
	ofLogError() << "SORRY OPEN LAST SAVE IS ONLY IMPLEMENTED ON LINUX";
#endif
}

//Page Handling ------------------------------------------------------------------------------

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

void ofxLibharu::setCmykBackground(float c, float m, float y, float k) {
	HPDF_Page_SetCMYKFill(page, c, m, y, k);
	HPDF_Page_Fill(page);
}

void ofxLibharu::setCmykForeground(float c, float m, float y, float k) {
	HPDF_Page_SetCMYKStroke(page, c, m, y, k);
	HPDF_Page_Stroke(page);
}

void ofxLibharu::disableBackground() {
	HPDF_Page_Eofill(page);
}

void ofxLibharu::disableForeground() {
	HPDF_Page_EofillStroke(page);
}


//Utilities ------------------------------------------------------------------------------

float ofxLibharu::convertDistance(float f) {
	return f * pixelRatio.x;
}

float ofxLibharu::convertX(float x) {
	return x * pixelRatio.x;
}

float ofxLibharu::convertY(float y) {
	return (pageSize.y - y) * pixelRatio.y;
}


void ofxLibharu::RGBToCMYK(int R, int G, int B, int &C, int &M, int &Y, int &K) {
	C = 1 - (R / 255);
	M = 1 - (G / 255);
	Y = 1 - (B / 255);
	int TempK = 1;
	if (C < TempK) TempK = C;
	if (M < TempK) TempK = M;
	if (Y < TempK) TempK = Y;
	if (TempK == 1) {
		C = M = Y = 0;
	} else {
		C = (C - TempK) / (1 - TempK);
		M = (M - TempK) / (1 - TempK);
		Y = (Y - TempK) / (1 - TempK);
	}
	K = TempK;
}


//Font Handling ---------------------------------------------------------------------------------

void ofxLibharu::setFontSyles() {
	setFillStyles();
	HPDF_Page_SetFontAndSize(page, font, fontSize);
	HPDF_Page_SetWordSpace(page, wordSpace);
	HPDF_Page_SetCharSpace(page, charSpace);
	HPDF_Page_SetTextLeading(page, textLeading);
}

void ofxLibharu::drawText(string text, float x, float y) {
	HPDF_Page_BeginText(page);
	HPDF_Page_MoveTextPos(page, convertX(x), convertY(y));
	setFontSyles();
	HPDF_Page_ShowText (page,text.c_str());
	HPDF_Page_EndText(page);
}

void ofxLibharu::drawTextBox(string text, float x, float y, float width, float height) {
	HPDF_Page_BeginText(page);
	HPDF_Page_MoveTextPos(page, convertX(x), convertY(y));
	setFontSyles();

	float right = convertX(x+width);
	float bottom = convertY(y+height);
	HPDF_Page_TextRect(page,convertX(x),convertY(y),right, bottom, text.c_str(),(_HPDF_TextAlignment)textAlignment, NULL);
	HPDF_Page_EndText(page);
}

void ofxLibharu::setFont(string _fontName) {
	fontName = _fontName;
	font = HPDF_GetFont (pdf, fontName.c_str(), NULL);
}

void ofxLibharu::setFontSize(float size) {
	fontSize = convertDistance(size);
}

void ofxLibharu::setTextAlignment(TEXT_ALIGNMENT _textAlignment) {
	// -> Some Issues in combination with  char spacing
	textAlignment = _textAlignment;
}

void ofxLibharu::setCharSpacing(float _charSpace) {
	charSpace = convertDistance(_charSpace);
}

void ofxLibharu::setWordSpacing(float _wordSpace) {
	wordSpace = convertDistance(_wordSpace);
}

void ofxLibharu::setTextLeading(float _textLeading) {
	textLeading = convertDistance(_textLeading);
}

void ofxLibharu::resetTextLeading() {
	setTextLeading(0);
}

//Graphics ---------------------------------------------------------------------------------

void ofxLibharu::setFillStyles() {
	HPDF_Page_SetCMYKFill(page,fillColor.c, fillColor.m, fillColor.y, fillColor.k);
	HPDF_Page_SetCMYKStroke(page,strokeColor.c, strokeColor.m, strokeColor.y, strokeColor.k);
}

void ofxLibharu::setGraphicStyles() {
	setFillStyles();
	HPDF_Page_SetLineWidth(page, lineWidth);
	HPDF_Page_SetLineJoin(page, (HPDF_LineJoin)lineJoin);
	HPDF_Page_SetLineCap(page, (HPDF_LineCap)lineCap);
}

void ofxLibharu::drawPathObject() {
	if(fillFlag==OF_FILLED) HPDF_Page_Fill(page);
	if(fillFlag==OF_OUTLINE) HPDF_Page_Stroke(page);
}

void ofxLibharu::drawCircle(float x, float y, float radius) {
	x = convertX(x);
	y = convertY(y);
	setGraphicStyles();
	HPDF_Page_Circle(page, x, y, convertDistance(radius));
	drawPathObject();
}

void ofxLibharu::drawEllipse(float x, float y, float width, float height) {
	x = convertX(x);
	y = convertY(y);
	setGraphicStyles();
	HPDF_Page_Ellipse(page, x, y, convertDistance(width), convertDistance(height));
	drawPathObject();
}

void ofxLibharu::drawLine(float x1, float y1, float x2, float y2) {
	x1 = convertX(x1);
	y1 = convertY(y1);
	x2 = convertX(x2);
	y2 = convertY(y2);
	setGraphicStyles();

	HPDF_Page_MoveTo(page, x1, y1);
	HPDF_Page_LineTo(page, x2, y2);
	drawPathObject();
}

/*void ofxLibharu::drawPolyLine(ofPolyline polyLine, bool close) {
	
}*/

void ofxLibharu::drawRectangle(float x, float y, float width, float height) {

	setGraphicStyles();
	HPDF_Page_Rectangle(page, convertX(x), convertY(y), convertDistance(width), -convertDistance(height));
	drawPathObject();
}

void ofxLibharu::setFillColor(float r, float g, float b) {
	int c, m, y, k;
	RGBToCMYK(r,g,b,c,m,y,k);
	setFillColor(c, m, y, k);
}

void ofxLibharu::setFillColor(float c, float m, float y, float k) {
	fillColor.c = c;
	fillColor.m = m;
	fillColor.y = y;
	fillColor.k = k;
}

void ofxLibharu::setStrokeColor(float r, float g, float b) {
	int c, m, y, k;
	RGBToCMYK(r,g,b,c,m,y,k);
	setStrokeColor(c, m, y, k);
}

void ofxLibharu::setStrokeColor(float c, float m, float y, float k) {
	strokeColor.c = c;
	strokeColor.m = m;
	strokeColor.y = y;
	strokeColor.k = k;
}

void ofxLibharu::setLineWidth(float _width) {
	lineWidth = convertDistance(_width);
}

void ofxLibharu::setFillType(ofFillFlag _fillFlag) {
	fillFlag = _fillFlag;
}

void ofxLibharu::setLineCapStyle(LINE_CAP _lineCap) {
	lineCap = _lineCap;
}

void ofxLibharu::setLineJoinStyle(LINE_JOIN _lineJoin) {
	lineJoin = _lineJoin;
}
