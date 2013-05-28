#ifndef OFXLIBHARU_H
#define OFXLIBHARU_H

#include "ofMain.h"
#include "hpdf.h"
#include "ofxlibharuErrors.h"

class ofxLibharu {
public:

	class CMYK{
	public:
		CMYK(){
			cyan = magenta = yellow = 0;
			black = 1;
		}
	
		CMYK(float c, float m, float y, float k){
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

	ofxLibharu();
	~ofxLibharu();

	void setup(PAGE_SIZE size = A4, ORIENTATION o = PORTRAIT);

	void setPageSize(PAGE_SIZE size);
	void setPageSize(PAGE_SIZE size, ORIENTATION o);
	void setPageSize(float x, float y);
	void setOrientation(ORIENTATION o);
	void setDPI(int dpi);

	void newPage();
	void newPage(PAGE_SIZE size, ORIENTATION o = PORTRAIT);
	void newPage(float w, float h);

	void save(string path, bool inDataFolder = true);
	void openLastSave();
	
	void setCmykBackground(float c, float m, float y, float k);
	void setCmykForeground(float c, float m, float y, float k);
	
	void disableBackground();
	void disableForeground();

private:
	
	void updatePage();
	ofVec2f pageSize;
	ofVec2f pixelRatio;
	ORIENTATION orientation;
	float dpi;
	bool hasDPI;

	float convertX(float x);
	float convertY(float y);
	float convertDistance(float f);

	HPDF_Doc  pdf;
	HPDF_Page page;
	
	string lastFileSaved;
	
	CMYK color;
	
	ofFillFlag fillFlag;
	bool bLineSmoothing;
	float lineWidth;
};

#endif // OFXLIBHARU_H
