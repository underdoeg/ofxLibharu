#ifndef OFXLIBHARU_H
#define OFXLIBHARU_H

#include "ofMain.h"
#include "hpdf.h"
ofGLRenderer
class ofxLibharu: public ofBaseRenderer {
public:
	enum PAGE_SIZE {
	    A5,
	    A4,
	    A3,
	    US_LETTER
	};

	enum ORIENTATION {
	    PORTRAIT,
	    LANDSCAPE
	};

	ofxLibharu();
	~ofxLibharu();

	void setup(PAGE_SIZE size = A4, ORIENTATION o = PORTRAIT);

	void setPageSize(PAGE_SIZE size);
	void setPageSize(float x, float y);
	void setOrientation(ORIENTATION o);

	void newPage();
	void newPage(PAGE_SIZE size, ORIENTATION o = PORTRAIT);
	void newPage(float w, float h);

	void save(string path, bool inDataFolder = true);

	/********** FUNCTIONS FOR OF BASE RENDERER *******************************/
	string getType();

	bool bClearBg();
	void background(const ofColor& c);
	void background(float brightness);
	void background(int hexColor, float _a = 255.0f);
	void background(int r, int g, int b, int a = 255);

	void draw(ofFloatImage& image, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh);
	void draw(ofImage& image, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh);
	void draw(ofPath& shape);
	void draw(ofPolyline& poly);
	void draw(ofShortImage& image, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh);
	void draw(vector<ofPoint>& vertexData, ofPrimitiveMode drawMode);
	void drawCircle(float x, float y, float z, float radius);
	void drawEllipse(float x, float y, float z, float width, float height);
	void drawLine(float x1, float y1, float z1, float x2, float y2, float z2);
	void drawRectangle(float x, float y, float z, float w, float h);
	void drawString(string text, float x, float y, float z, ofDrawBitmapMode mode);
	void drawTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);

	ofFloatColor& getBgColor();
	ofRectangle getCurrentViewport();
	ofFillFlag getFillMode();
	ofRectMode getRectMode();

	int getViewportHeight();
	int getViewportWidth();
	void loadIdentityMatrix(void);
	void loadMatrix(const float* m);
	void loadMatrix(const ofMatrix4x4& m);
	void matrixMode(ofMatrixMode mode);
	void multMatrix(const float* m);
	void multMatrix(const ofMatrix4x4& m);
	void popMatrix();
	void popView();
	void pushMatrix();
	void pushView();
	bool rendersPathPrimitives();
	void rotate(float degrees);
	void rotate(float degrees, float vecX, float vecY, float vecZ);
	void rotateX(float degrees);
	void rotateY(float degrees);
	void scale(float xAmnt, float yAmnt, float zAmnt = 1);
	void setBackgroundAuto(bool bManual);
	void setBlendMode(ofBlendMode blendMode);
	void setCircleResolution(int res);
	void setColor(const ofColor& color);
	void setColor(const ofColor& color, int _a);
	void setColor(int gray);
	void setColor(int r, int g, int b);
	void setColor(int r, int g, int b, int a);
	void setFillMode(ofFillFlag fill);
	void setHexColor(int hexColor);
	void setLineSmoothing(bool smooth);
	void setLineWidth(float lineWidth);
	void setRectMode(ofRectMode mode);
	void setSphereResolution(int res);
	void setupGraphicDefaults();
	void translate(const ofPoint& p);
	void translate(float x, float y, float z = 0);
	void viewport(float x = 0, float y = 0, float width = 0, float height = 0, bool invertY = true);
	void viewport(ofRectangle viewport);

private:
	ofVec2f pageSize;
	ORIENTATION orientation;

	float convertX(float x);
	float convertY(float y);

	HPDF_Doc  pdf;
	HPDF_Page page;
};

#endif // OFXLIBHARU_H
