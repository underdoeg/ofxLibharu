#include "ofxlibharu.h"

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data) {
}

ofxLibharu::ofxLibharu() {
}

ofxLibharu::~ofxLibharu() {
	HPDF_Free(pdf);
}

void ofxLibharu::setup(PAGE_SIZE size, ORIENTATION o) {
	setPageSize(size);
	setOrientation(o);
	pdf = HPDF_New (error_handler, NULL);
	newPage();
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
	}
	setOrientation(orientation);
}

void ofxLibharu::setPageSize(float x, float y) {
	pageSize.set(x, y);
}

void ofxLibharu::setOrientation(ORIENTATION o) {
	orientation = o;
	if(orientation == PORTRAIT) {
		if(pageSize.x > pageSize.y)
			pageSize.set(pageSize.y, pageSize.x);
	} else if(orientation == LANDSCAPE) {
		if(pageSize.y > pageSize.x)
			pageSize.set(pageSize.x, pageSize.y);
	}
}

void ofxLibharu::newPage(PAGE_SIZE size, ORIENTATION o) {
	setPageSize(size);
	setOrientation(o);
	newPage();
}
void ofxLibharu::newPage(float w, float h) {
	setPageSize(w, h);
}

void ofxLibharu::newPage() {
	page = HPDF_AddPage(pdf);

	HPDF_Page_MoveTo(page, 0, 0);
	HPDF_Page_LineTo(page, 200, 200);
	HPDF_Page_Stroke(page);
}

void ofxLibharu::save(string path, bool inDataFolder) {
	if(inDataFolder)
		path = ofToDataPath(path, true);
	HPDF_SaveToFile(pdf, path.c_str());
}

float ofxLibharu::convertX(float x)
{
	return x;
}

float ofxLibharu::convertY(float y)
{
	return pageSize.y - y;
}


/********** FUNCTIONS FOR OF BASE RENDERER *******************************/
bool ofxLibharu::bClearBg()
{
}

void ofxLibharu::background(const ofColor& c)
{
}

void ofxLibharu::background(float brightness)
{
}

void ofxLibharu::background(int hexColor, float _a)
{
}

void ofxLibharu::background(int r, int g, int b, int a)
{
}

void ofxLibharu::draw(ofFloatImage& image, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh)
{
	x = convertX(x);
	y = convertY(y);
}

void ofxLibharu::draw(ofImage& image, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh)
{
	x = convertX(x);
	y = convertY(y);
}

void ofxLibharu::draw(ofPath& shape)
{
}

void ofxLibharu::draw(ofPolyline& poly)
{
}

void ofxLibharu::draw(ofShortImage& image, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh)
{
	x = convertX(x);
	y = convertY(y);
}

void ofxLibharu::draw(vector<ofPoint>& vertexData, ofPrimitiveMode drawMode)
{
}

void ofxLibharu::drawCircle(float x, float y, float z, float radius)
{
	x = convertX(x);
	y = convertY(y);
}

void ofxLibharu::drawEllipse(float x, float y, float z, float width, float height)
{
	x = convertX(x);
	y = convertY(y);
}

void ofxLibharu::drawLine(float x1, float y1, float z1, float x2, float y2, float z2)
{
	x1 = convertX(x1);
	y1 = convertY(y1);
	x2 = convertX(x2);
	y2 = convertY(y2);
}

void ofxLibharu::drawRectangle(float x, float y, float z, float w, float h)
{
	x = convertX(x);
	y = convertY(y);
}

void ofxLibharu::drawString(string text, float x, float y, float z, ofDrawBitmapMode mode)
{
	x = convertX(x);
	y = convertY(y);
}

void ofxLibharu::drawTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
	x1 = convertX(x1);
	y1 = convertY(y1);
	x2 = convertX(x2);
	y2 = convertY(y2);
	x3 = convertX(x3);
	y3 = convertY(y3);
}

ofFloatColor& ofxLibharu::getBgColor()
{
}

ofRectangle ofxLibharu::getCurrentViewport()
{
}

ofFillFlag ofxLibharu::getFillMode()
{
}

ofRectMode ofxLibharu::getRectMode()
{
}

string ofxLibharu::getType()
{
}

int ofxLibharu::getViewportHeight()
{
}

int ofxLibharu::getViewportWidth()
{
}

void ofxLibharu::loadIdentityMatrix(void)
{
}

void ofxLibharu::loadMatrix(const float* m)
{
}

void ofxLibharu::loadMatrix(const ofMatrix4x4& m)
{
}

void ofxLibharu::matrixMode(ofMatrixMode mode)
{
}

void ofxLibharu::multMatrix(const float* m)
{
}

void ofxLibharu::multMatrix(const ofMatrix4x4& m)
{
}

void ofxLibharu::popMatrix()
{
}

void ofxLibharu::popView()
{
}

void ofxLibharu::pushMatrix()
{
}

void ofxLibharu::pushView()
{
}

bool ofxLibharu::rendersPathPrimitives()
{
}

void ofxLibharu::rotate(float degrees)
{
}

void ofxLibharu::rotate(float degrees, float vecX, float vecY, float vecZ)
{
}

void ofxLibharu::rotateX(float degrees)
{
}

void ofxLibharu::rotateY(float degrees)
{
}

void ofxLibharu::scale(float xAmnt, float yAmnt, float zAmnt)
{
}

void ofxLibharu::setBackgroundAuto(bool bManual)
{
}

void ofxLibharu::setBlendMode(ofBlendMode blendMode)
{
}

void ofxLibharu::setCircleResolution(int res)
{
}

void ofxLibharu::setColor(const ofColor& color)
{
}

void ofxLibharu::setColor(const ofColor& color, int _a)
{
}

void ofxLibharu::setColor(int gray)
{
}

void ofxLibharu::setColor(int r, int g, int b)
{
}

void ofxLibharu::setColor(int r, int g, int b, int a)
{
}

void ofxLibharu::setFillMode(ofFillFlag fill)
{
}

void ofxLibharu::setHexColor(int hexColor)
{
	int r = (hexColor >> 16) & 0xff;
	int g = (hexColor >> 8) & 0xff;
	int b = (hexColor >> 0) & 0xff;
	setColor(r,g,b);
}

void ofxLibharu::setLineSmoothing(bool smooth)
{
}

void ofxLibharu::setLineWidth(float lineWidth)
{
}

void ofxLibharu::setRectMode(ofRectMode mode)
{
}

void ofxLibharu::setSphereResolution(int res)
{
}

void ofxLibharu::setupGraphicDefaults()
{
}

void ofxLibharu::translate(const ofPoint& p)
{
}

void ofxLibharu::translate(float x, float y, float z)
{
}

void ofxLibharu::viewport(float x, float y, float width, float height, bool invertY)
{
}

void ofxLibharu::viewport(ofRectangle viewport)
{
}

