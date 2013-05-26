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
	//check https://github.com/libharu/libharu/wiki/Error-handling#wiki-List_of_error_codes for error codes
}

ofxLibharu::ofxLibharu() {
	selfPtr = ofPtr<ofBaseRenderer>(this);
	setDPI(300);
	setPageSize(A4);
}

ofxLibharu::~ofxLibharu() {
	HPDF_Free(pdf);
}

void ofxLibharu::setup(PAGE_SIZE size, ORIENTATION o) {
	pdf = HPDF_New (error_handler, NULL);
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

float ofxLibharu::convertX(float x) {
	return x * pixelRatio.x;
}

float ofxLibharu::convertY(float y) {
	return (pageSize.y - y) * pixelRatio.y;
}

void ofxLibharu::enable() {
	oldRendererPtr = ofGetCurrentRenderer();
	ofSetCurrentRenderer(selfPtr);
}

void ofxLibharu::disable() {
	ofSetCurrentRenderer(oldRendererPtr);
}


/********** FUNCTIONS FOR OF BASE RENDERER *******************************/
bool ofxLibharu::bClearBg() {
}

void ofxLibharu::background(const ofColor& c) {
	background(c.r, c.g, c.b, c.a);
}

void ofxLibharu::background(float brightness) {
	background(brightness, brightness, brightness, 255);
}

void ofxLibharu::background(int hexColor, float _a) {

}

void ofxLibharu::background(int r, int g, int b, int a) {

}

void ofxLibharu::draw(ofFloatImage& image, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh) {
	x = convertX(x);
	y = convertY(y);
}

void ofxLibharu::draw(ofImage& image, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh) {
	x = convertX(x);
	y = convertY(y);
}

void ofxLibharu::draw(ofPath& shape) {
}

void ofxLibharu::draw(ofPolyline& poly) {
}

void ofxLibharu::draw(ofShortImage& image, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh) {
	x = convertX(x);
	y = convertY(y);
}

void ofxLibharu::draw(vector<ofPoint>& vertexData, ofPrimitiveMode drawMode) {
}

void ofxLibharu::drawCircle(float x, float y, float z, float radius) {
	x = convertX(x);
	y = convertY(y);
}

void ofxLibharu::drawEllipse(float x, float y, float z, float width, float height) {
	x = convertX(x);
	y = convertY(y);
}

void ofxLibharu::drawLine(float x1, float y1, float z1, float x2, float y2, float z2) {
	x1 = convertX(x1);
	y1 = convertY(y1);
	x2 = convertX(x2);
	y2 = convertY(y2);
	HPDF_Page_MoveTo(page, x1, y1);
	HPDF_Page_LineTo(page, x2, y2);
	HPDF_Page_Stroke(page);
}

void ofxLibharu::drawRectangle(float x, float y, float z, float w, float h) {
	x = convertX(x);
	y = convertY(y);
}

void ofxLibharu::drawString(string text, float x, float y, float z, ofDrawBitmapMode mode) {
	x = convertX(x);
	y = convertY(y);
}

void ofxLibharu::drawTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
	x1 = convertX(x1);
	y1 = convertY(y1);
	x2 = convertX(x2);
	y2 = convertY(y2);
	x3 = convertX(x3);
	y3 = convertY(y3);
}

ofFloatColor& ofxLibharu::getBgColor() {
}

ofRectangle ofxLibharu::getCurrentViewport() {
}

ofFillFlag ofxLibharu::getFillMode() {
}

ofRectMode ofxLibharu::getRectMode() {
}

string ofxLibharu::getType() {
	return "PDF";
}

int ofxLibharu::getViewportHeight() {
}

int ofxLibharu::getViewportWidth() {
}

void ofxLibharu::loadIdentityMatrix(void) {
}

void ofxLibharu::loadMatrix(const float* m) {
}

void ofxLibharu::loadMatrix(const ofMatrix4x4& m) {
}

void ofxLibharu::matrixMode(ofMatrixMode mode) {
}

void ofxLibharu::multMatrix(const float* m) {
}

void ofxLibharu::multMatrix(const ofMatrix4x4& m) {
}

void ofxLibharu::popMatrix() {
}

void ofxLibharu::popView() {
}

void ofxLibharu::pushMatrix() {
}

void ofxLibharu::pushView() {
}

bool ofxLibharu::rendersPathPrimitives() {
}

void ofxLibharu::rotate(float degrees) {
}

void ofxLibharu::rotate(float degrees, float vecX, float vecY, float vecZ) {
}

void ofxLibharu::rotateX(float degrees) {
}

void ofxLibharu::rotateY(float degrees) {
}

void ofxLibharu::scale(float xAmnt, float yAmnt, float zAmnt) {
}

void ofxLibharu::setBackgroundAuto(bool bManual) {
}

void ofxLibharu::setBlendMode(ofBlendMode blendMode) {
}

void ofxLibharu::setCircleResolution(int res) {
}

void ofxLibharu::setColor(const ofColor& color) {
}

void ofxLibharu::setColor(const ofColor& color, int _a) {
}

void ofxLibharu::setColor(int gray) {
}

void ofxLibharu::setColor(int r, int g, int b) {
}

void ofxLibharu::setColor(int r, int g, int b, int a) {
}

void ofxLibharu::setFillMode(ofFillFlag fill) {
}

void ofxLibharu::setHexColor(int hexColor) {
	int r = (hexColor >> 16) & 0xff;
	int g = (hexColor >> 8) & 0xff;
	int b = (hexColor >> 0) & 0xff;
	setColor(r,g,b);
}

void ofxLibharu::setLineSmoothing(bool smooth) {
}

void ofxLibharu::setLineWidth(float lineWidth) {
}

void ofxLibharu::setRectMode(ofRectMode mode) {
}

void ofxLibharu::setSphereResolution(int res) {
}

void ofxLibharu::setupGraphicDefaults() {
}

void ofxLibharu::translate(const ofPoint& p) {
}

void ofxLibharu::translate(float x, float y, float z) {
}

void ofxLibharu::viewport(float x, float y, float width, float height, bool invertY) {
}

void ofxLibharu::viewport(ofRectangle viewport) {
}
void ofxLibharu::draw(of3dPrimitive& model, ofPolyRenderMode renderType) {
}

void ofxLibharu::draw(ofMesh& vertexData, bool useColors, bool useTextures, bool useNormals) {
}

void ofxLibharu::draw(ofMesh& vertexData, ofPolyRenderMode renderType, bool useColors, bool useTextures, bool useNormals) {
}

void ofxLibharu::update() {
}

