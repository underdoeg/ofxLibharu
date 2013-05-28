#ifndef OFXLIBHARU_H
#define OFXLIBHARU_H

#include "ofMain.h"
#include "hpdf.h"
#include "ofxlibharuErrors.h"

class ofxLibharu {
public:

	class CMYK {
	public:
		CMYK() {
			cyan = magenta = yellow = 0;
			black = 1;
		}

		CMYK(float c, float m, float y, float k) {
			cyan = c;
			magenta = m;
			yellow = y;
			black = k;
		}

		float cyan, magenta, yellow, black;
	};

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

	enum TEXT_ALIGNMENT {
	    ALIGN_LEFT,
	    ALIGN_RIGHT,
	    ALIGN_CENTER,
	    ALIGN_JUSTIFY
	};

	enum LINE_CAP {
	    LINE_CAP_BUTT,
	    LINE_CAP_ROUND,
	    LINE_CAP_PROJECTING_SCUARE,
	    LINE_CAP_EOF
	};

	enum LINE_JOIN {
	    LINE_JOIN_MITER,
	    LINE_JOIN_ROUND,
	    LINE_JOIN_BEVEL,
	    LINE_JOIN_EOF
	};

	ofxLibharu();
	~ofxLibharu();

	//Document Handling
	void setup(PAGE_SIZE size = A4, ORIENTATION o = PORTRAIT);

	void save(string path, bool inDataFolder = true);
	void openLastSave();

	//Page Handling
	void setPageSize(PAGE_SIZE size);
	void setPageSize(PAGE_SIZE size, ORIENTATION o);
	void setPageSize(float x, float y);
	void setOrientation(ORIENTATION o);
	void setDPI(int dpi);

	void newPage();
	void newPage(PAGE_SIZE size, ORIENTATION o = PORTRAIT);
	void newPage(float w, float h);

	void setCmykBackground(float c, float m, float y, float k);
	void setCmykForeground(float c, float m, float y, float k);

	void disableBackground();
	void disableForeground();

	//Graphics
	void setFillColor(float r, float g, float b);
	void setFillColor(float c, float m, float y, float k);
	void setStrokeColor(float r, float g, float b);
	void setStrokeColor(float c, float m, float y, float k);
	void setLineWidth(float width);
	void setFillType(ofFillFlag fillFlag);
	void setLineCapStyle(LINE_CAP lineCap);
	void setLineJoinStyle(LINE_JOIN lineJoin);

	void drawRectangle(float x, float y, float width, float height);
	void drawLine(float x1, float y1, float x2, float y2);
	void drawCircle(float x, float y, float radius);
	void drawEllipse(float x, float y, float width, float height);
	//void drawPolyLine(ofPolyline polyLine, bool close = false);


	//Font Handling
	void setFont(string fontName);
	void setFontSize(float size);
	void setTextAlignment(TEXT_ALIGNMENT textAlignment);
	void setCharSpacing(float charSpace);
	void setWordSpacing(float wordSpace);
	void setTextLeading(float textLeading);
	void resetTextLeading();
	void drawText(string text, float x, float y);
	void drawTextBox(string text, float x, float y, float width, float height);
	

private:

	//Document Handling
	ofVec2f pixelRatio;
	ORIENTATION orientation;
	HPDF_Doc  pdf;
	float dpi;
	bool hasDPI;

	//Page Handling
	void updatePage();
	ofVec2f pageSize;
	HPDF_Page page;

	string lastFileSaved;

	//Utitilies
	float convertX(float x);
	float convertY(float y);
	float convertDistance(float f);
	void RGBToCMYK(int R, int G, int B, int &C, int &M, int &Y, int &K);

	//Graphics
	void setFillStyles();
	void setGraphicStyles();
	void drawPathObject();
	bool bLineSmoothing;
	float lineWidth;
	bool doFill;
	bool doStroke;
	_HPDF_CMYKColor fillColor;
	_HPDF_CMYKColor strokeColor;
	ofFillFlag fillFlag;
	LINE_CAP lineCap;
	LINE_JOIN lineJoin;

	//Font Handling
	void setFontSyles();
	float fontSize;
	float charSpace;
	float wordSpace;
	float textLeading;
	string fontName;
	TEXT_ALIGNMENT textAlignment;

	HPDF_Font font;


};

#endif // OFXLIBHARU_H
