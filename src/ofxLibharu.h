#ifndef OFXLIBHARU_H
#define OFXLIBHARU_H

#include "ofMain.h"
#include "hpdf.h"
#include "ofxLibharuErrors.h"

class ofxLibharu {
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

	enum TEXT_ALIGNMENT {
	    ALIGN_LEFT,
	    ALIGN_RIGHT,
	    ALIGN_CENTER,
	    ALIGN_JUSTIFY,
		ALIGN_JUSTIFY_ALL
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

	void newPage(PAGE_SIZE size, ORIENTATION o = PORTRAIT);
	void newPage(float w, float h);

	void setCmykBackground(float c, float m, float y, float k);
	void setCmykForeground(float c, float m, float y, float k);

	void disableBackground();
	void disableForeground();

	void resetStyles();

	ofVec2f getPageSize();

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
	void setTTFontFromFile(string filename);
	void setFontSize(float size);
	void setTextAlignment(TEXT_ALIGNMENT textAlignment);
	void setCharSpacing(float charSpace);
	void setWordSpacing(float wordSpace);
	void setTextLeading(float textLeading);
	void resetTextLeading();
	void drawText(string text, float x, float y);
	void drawTextBox(string text, float x, float y, float width, float height);

	float getTextWidth(string text, string font, float fontSize, float charSpacing, float wordSpacing);
	float getTextWidth(string text);
	float getTextLeading();

	float getFontDescent(string font, float fontSize);
	float getFontDescent();
	float getFontAscent(string font, float fontSize);
	float getFontAscent();
	float getFontCapHeight(string font, float fontSize);
	float getFontCapHeight();
	float getFontXHeight(string font, float fontSize);
	float getFontXHeight();

	int measureText(float width, string text, string fontName, float fontSize, float charSpacing, float wordSpacing);
	int measureTextBox(float width, float height, string text, string fontName, float fontSize, float textLeading, float charSpacing, float wordSpacing);
	float getTextBoxHeight(float width, string text, string fontName, float fontSize, float textLeading, float charSpacing, float wordSpacing);


private:

	//Document Handling
	ofVec2f pixelRatio;
	ORIENTATION orientation;
	HPDF_Doc  pdf;
	float dpi;
	bool hasDPI;
	string encoding;

	HPDF_Doc tmpPdf;
	HPDF_Page tmpPage;
	void createTmpPage();

	//Page Handling
	void newPage();
	void updatePage();
	void setDefaultValues();
	ofVec2f pageSize;

	HPDF_Page page;

	string lastFileSaved;

	//Utitilies
	float convertX2Libh(float x);
	float convertY2Libh(float y);
	float convertDistance2Libh(float f);
	float convertX2OF(float x);
	float convertY2OF(float y);
	float convertDistance2OF(float f);
	void RGBToCMYK(int R, int G, int B, int &C, int &M, int &Y, int &K);

	//Graphics
	void setFillStyles();
	void setGraphicStyles();
	void drawPathObject();
	float lineWidth;
	_HPDF_CMYKColor fillColor;
	_HPDF_CMYKColor strokeColor;
	ofFillFlag fillFlag;
	LINE_CAP lineCap;
	LINE_JOIN lineJoin;

	//Font Handling
	HPDF_Font getTmpFont(string fontName);
	void setFontSyles();
	void drawWord(string word, float x, float y);
	float fontSize, fontSize_OF;
	float charSpace, charSpace_OF;
	float wordSpace, wordSpace_OF;
	float textLeading, textLeading_OF;
	string fontName;
	TEXT_ALIGNMENT textAlignment;
	HPDF_Font font;

};

#endif // OFXLIBHARU_H
