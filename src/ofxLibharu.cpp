#include "ofxLibharu.h"

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
	doTransform = false;
}

ofxLibharu::~ofxLibharu() {
	HPDF_Free(pdf);
	HPDF_Free(tmpPdf);
}

//Document Handling ------------------------------------------------------------------------------

void ofxLibharu::setup(PAGE_SIZE size, ORIENTATION o) {
	pdf = HPDF_New (error_handler, NULL);
	HPDF_SetCompressionMode(pdf,HPDF_COMP_NONE);
	HPDF_UseUTFEncodings(pdf);
	encoding = "UTF-8";
	HPDF_SetCurrentEncoder(pdf, encoding.c_str());

	createTmpPage();

	setCmykBackground(0, 0, 0, 1);
	setCmykForeground(0, 0, 0, 1);
	newPage();
	setOrientation(o);
	setPageSize(size);
	setDefaultValues();
	
}

void ofxLibharu::createTmpPage() {

	tmpPdf = HPDF_New (error_handler, NULL);

	HPDF_UseUTFEncodings(tmpPdf);
	HPDF_SetCurrentEncoder(tmpPdf, encoding.c_str());

	tmpPage = HPDF_AddPage(tmpPdf);
	HPDF_Page_SetSize(tmpPage, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
	HPDF_Page_Concat (tmpPage, 72.0f / dpi, 0, 0, 72.0f / dpi, 0, 0);

}

void ofxLibharu::setDefaultValues() {

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

void ofxLibharu::resetStyles() {
	setDefaultValues();
}

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
	newPage();
	setPageSize(w, h);
}

void ofxLibharu::newPage() {
	hasDPI = false;
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

ofVec2f ofxLibharu::getPageSize() {
	return pageSize;
}


//Utilities ------------------------------------------------------------------------------

float ofxLibharu::convertDistance2Libh(float f) {
	return f * pixelRatio.x;
}

float ofxLibharu::convertX2Libh(float x) {
	return x * pixelRatio.x;
}

float ofxLibharu::convertY2Libh(float y) {
	return (pageSize.y - y) * pixelRatio.y;
}

float ofxLibharu::convertDistance2OF(float f) {
	return f*1/pixelRatio.x;
}

float ofxLibharu::convertX2OF(float x) {
	return x*1/pixelRatio.x;
}

float ofxLibharu::convertY2OF(float y) {
	return pageSize.y - y*1/pixelRatio.y;
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

HPDF_Font ofxLibharu::getTmpFont(string _fontName) {
	HPDF_Font tmpFont;
	if(ofIsStringInString(_fontName,".ttf")) {
		const char *ttfFont = HPDF_LoadTTFontFromFile(tmpPdf, _fontName.c_str(), HPDF_TRUE);
		tmpFont = HPDF_GetFont(tmpPdf, ttfFont, encoding.c_str());
	} else {
		tmpFont = HPDF_GetFont (tmpPdf, _fontName.c_str(), NULL);
	}
	return tmpFont;
}

int ofxLibharu::measureText(float _width, string _text, string _fontName, float _fontSize, float _charSpacing, float _wordSpacing) {

	float defWidth = convertDistance2Libh(_width-charSpace_OF);
	float defFontSize = convertDistance2Libh(_fontSize);
	float defCharSpacing = convertDistance2Libh(_charSpacing);
	float defWordSpacing = convertDistance2Libh(_wordSpacing);

	HPDF_UINT len = strlen(_text.c_str());
	int tmpCharCount = HPDF_Font_MeasureText(getTmpFont(_fontName), (HPDF_BYTE *)_text.c_str(), len, defWidth, defFontSize, defCharSpacing, defWordSpacing, HPDF_TRUE, NULL);

	return tmpCharCount;
}

float ofxLibharu::getTextBoxHeight(float _width, string _text, string _fontName, float _fontSize, float _textLeading, float _charSpacing, float _wordSpacing) {
	int charCount = 1;
	string fillText = _text;
	int lineCount = 0;

	while(charCount>0) {
		charCount = measureText(_width,fillText,_fontName,_fontSize,_charSpacing,_wordSpacing);
		fillText.erase(0,charCount);
		if(charCount!=0) lineCount++;
	}

	float height = lineCount*_textLeading;
	height+=_fontSize;
	height-= _textLeading;
	height+=getFontDescent(_fontName,_fontSize)*-1;
	return height;
}

int ofxLibharu::measureTextBox(float _width, float _height, string _text, string _fontName, float _fontSize, float _textLeading, float _charSpacing, float _wordSpacing) {

	string fillText = _text;
	float countHeight=_fontSize+getFontDescent(_fontName,_fontSize)*-1;

	int charCount = 0;
	int curChar = 0;

	while(countHeight<_height) {
		charCount = measureText(_width,fillText,_fontName,_fontSize,_charSpacing,_wordSpacing);
		fillText.erase(0,charCount);
		countHeight+=_textLeading;
	}

	return fillText.size();
}

void ofxLibharu::drawTextBox(string text, float x, float y, float width, float height) {

	//float maxHeight = height-getFontDescent(fontName,convertDistance2OF(fontSize))*-1;
	for(float ypos=fontSize_OF; ypos<=height; ypos+=textLeading_OF) {
		int charCount = measureText(width,text,fontName,fontSize_OF,charSpace_OF,wordSpace_OF);
		string defText = text.substr(0,charCount);
		text.erase(0,charCount);

		//remove spaces on end of line
		while(defText[defText.size()-1]==' ') {
			defText = defText.substr(0,defText.size()-1);
		}
		
		//get new text widh
		float defTextWidth = getTextWidth(defText, fontName, fontSize_OF, charSpace_OF,wordSpace_OF);
		float defx;

		switch(textAlignment) {
		case ALIGN_LEFT:
			defx = x;
			break;
		case ALIGN_RIGHT:
			defx = x+width-defTextWidth;
			break;
		case ALIGN_CENTER:
			defx = x+(width-defTextWidth)*.5;
			break;
		case ALIGN_JUSTIFY:
			defx = x;
			break;
		case ALIGN_JUSTIFY_ALL:
			defx = x;
			break;
		default:
			defx = x;
			break;
		}

		//set wordspacing for ALIGN_JUSTIFY
		//removed wordspacing oversize error in hpdf_page_operator.c line 1062-1063
		float prevWordSpacing = wordSpace_OF;
		if(textAlignment==ALIGN_JUSTIFY && ypos<height-textLeading_OF || textAlignment==ALIGN_JUSTIFY_ALL) {
			HPDF_TextWidth tw = HPDF_Font_TextWidth (font, (HPDF_BYTE *)defText.c_str(),  defText.size());
			float additionalWordSpacing = (width-defTextWidth)/(tw.numwords-1);
			setWordSpacing(wordSpace_OF+additionalWordSpacing);
		}

		drawText(defText,defx,y+ypos);

		// reset wordspacing
		if(textAlignment==ALIGN_JUSTIFY || textAlignment==ALIGN_JUSTIFY_ALL) setWordSpacing(prevWordSpacing);
	}

}

void ofxLibharu::drawWord(string text, float x, float y) {
	HPDF_Page_BeginText(page);
	HPDF_Page_MoveTextPos(page, convertX2Libh(x), convertY2Libh(y));
	setFontSyles();
	HPDF_Page_ShowText (page,text.c_str());
	HPDF_Page_EndText(page);
}



void ofxLibharu::drawText(string text, float x, float y) {
	vector<string> words = ofSplitString(text," ");

	float xpos = x;
	for(int i=0; i<words.size(); i++) {
		float wordWidth = getTextWidth(words[i]+" ", fontName, fontSize_OF, charSpace_OF, wordSpace_OF);
		drawWord(words[i],xpos,y);
		xpos+=wordWidth+convertDistance2OF(HPDF_Page_GetCharSpace(page));
	}
}

float ofxLibharu::getTextWidth(string _text, string _fontName, float _fontSize, float _charSpacing, float _wordSpacing) {

	HPDF_TextWidth tw = HPDF_Font_TextWidth (getTmpFont(_fontName), (HPDF_BYTE *)_text.c_str(),  _text.size());
	float textWidth = convertDistance2Libh(_wordSpacing)*tw.numspace;
	textWidth+= tw.width*convertDistance2Libh(_fontSize)/1000;
	textWidth+= convertDistance2Libh(_charSpacing)*tw.numchars;
	textWidth-= convertDistance2Libh(_charSpacing);

	return convertDistance2OF(textWidth);
}

float ofxLibharu::getTextWidth(string text) {
	float textWidth = HPDF_Page_TextWidth(page, text.c_str());
	return convertDistance2OF(textWidth-charSpace);
}

float ofxLibharu::getTextLeading() {
	float leading = HPDF_Page_GetTextLeading(page);
	leading*=fontSize*.001;
	return convertDistance2OF(leading);
}

float ofxLibharu::getFontXHeight(string _fontName, float _fontSize) {
	HPDF_Font tmpFont = getTmpFont(_fontName);

	float xHeight = HPDF_Font_GetXHeight(tmpFont);
	xHeight*=convertDistance2Libh(_fontSize)*.001;
	return convertDistance2OF(xHeight);
}

float ofxLibharu::getFontXHeight() {
	float xHeight = HPDF_Font_GetXHeight(font);
	xHeight*=fontSize*.001;
	return convertDistance2OF(xHeight);
}

float ofxLibharu::getFontAscent(string _fontName, float _fontSize) {
	HPDF_Font tmpFont = getTmpFont(_fontName);

	float ascent = HPDF_Font_GetAscent(tmpFont);
	ascent*=convertDistance2Libh(_fontSize)*.001;
	return convertDistance2OF(ascent);
}

float ofxLibharu::getFontAscent() {
	float ascent = HPDF_Font_GetAscent(font);
	ascent*=fontSize*.001;
	return convertDistance2OF(ascent);
}

float ofxLibharu::getFontCapHeight(string _fontName, float _fontSize) {
	HPDF_Font tmpFont = getTmpFont(_fontName);

	float capHeight = HPDF_Font_GetCapHeight(tmpFont);
	capHeight*=convertDistance2Libh(_fontSize)*.001;
	return convertDistance2OF(capHeight);
}

float ofxLibharu::getFontCapHeight() {
	float capHeight = HPDF_Font_GetCapHeight(font);
	capHeight*=fontSize*.001;
	return convertDistance2OF(capHeight);
}

float ofxLibharu::getFontDescent(string _fontName, float _fontSize) {
	HPDF_Font tmpFont = getTmpFont(_fontName);

	float descent = HPDF_Font_GetDescent(tmpFont);
	descent*=convertDistance2Libh(_fontSize)*.001;
	return convertDistance2OF(descent);
}

float ofxLibharu::getFontDescent() {
	float descent = HPDF_Font_GetDescent(font);
	descent*=fontSize*.001;
	return convertDistance2OF(descent);
}

void ofxLibharu::setFontSyles() {
	setFillStyles();
	HPDF_Page_SetFontAndSize(page, font, fontSize);
	HPDF_Page_SetWordSpace(page, wordSpace);
	HPDF_Page_SetCharSpace(page, charSpace);
	HPDF_Page_SetTextLeading(page, textLeading);
}

void ofxLibharu::setFont(string _fontName) {
	fontName = _fontName;
	font = HPDF_GetFont (pdf, fontName.c_str(), NULL);
}

void ofxLibharu::setTTFontFromFile(string filename) {
	const char *ttfFont = HPDF_LoadTTFontFromFile(pdf, filename.c_str(), HPDF_TRUE);
	fontName = filename;
	font = HPDF_GetFont(pdf, ttfFont, encoding.c_str());
}

void ofxLibharu::setTextAlignment(TEXT_ALIGNMENT _textAlignment) {
	textAlignment = _textAlignment;
}

void ofxLibharu::setFontSize(float size) {
	//max font size ??? remove: (HPDF_MAX_FONTSIZE hpdf_page_operator.c)
	fontSize_OF = size;
	fontSize = convertDistance2Libh(size);
}

void ofxLibharu::setCharSpacing(float _charSpace) {
	charSpace_OF = _charSpace;
	charSpace = convertDistance2Libh(_charSpace);
}

void ofxLibharu::setWordSpacing(float _wordSpace) {
	wordSpace_OF = _wordSpace;
	wordSpace = convertDistance2Libh(_wordSpace);
}

void ofxLibharu::setTextLeading(float _textLeading) {
	textLeading_OF = _textLeading;
	textLeading = convertDistance2Libh(_textLeading);
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
	x = convertX2Libh(x);
	y = convertY2Libh(y);
	setGraphicStyles();
	HPDF_Page_Circle(page, x, y, convertDistance2Libh(radius));
	drawPathObject();
}

void ofxLibharu::drawEllipse(float x, float y, float width, float height) {
	x = convertX2Libh(x);
	y = convertY2Libh(y);
	setGraphicStyles();
	HPDF_Page_Ellipse(page, x, y, convertDistance2Libh(width), convertDistance2Libh(height));
	drawPathObject();
}

void ofxLibharu::drawLine(float x1, float y1, float x2, float y2) {
	x1 = convertX2Libh(x1);
	y1 = convertY2Libh(y1);
	x2 = convertX2Libh(x2);
	y2 = convertY2Libh(y2);
	setGraphicStyles();

	HPDF_Page_MoveTo(page, x1, y1);
	HPDF_Page_LineTo(page, x2, y2);
	drawPathObject();
}

/*void ofxLibharu::drawPolyLine(ofPolyline polyLine, bool close) {

}*/

void ofxLibharu::drawRectangle(float x, float y, float width, float height) {

	setGraphicStyles();
	HPDF_Page_Rectangle(page, convertX2Libh(x), convertY2Libh(y), convertDistance2Libh(width), -convertDistance2Libh(height));
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
	lineWidth = convertDistance2Libh(_width);
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

void ofxLibharu::popMatrix(){
	HPDF_Page_GRestore(page);
	doTransform = false;
}

void ofxLibharu::pushMatrix(){
	HPDF_Page_GSave(page);
	doTransform = true;
}

void ofxLibharu::translate(float x, float y){
	
	float posx = convertDistance2Libh(x);
	float posy = convertDistance2Libh(y); 
	HPDF_Page_Concat (page, 1,0,0,1, posx,-posy);
}

void ofxLibharu::rotate(float angle, float originX, float originY){
			
    float rad1 = ofDegToRad(angle);
	float posx = convertX2Libh(originX);
	float posy = convertY2Libh(originY);

	HPDF_Page_Concat (page, 1,0,0,1, 100,-100);
    HPDF_Page_Concat (page, cos(rad1), sin(rad1), -sin(rad1), cos(rad1), posx,posy);
	HPDF_Page_Concat (page, 1,0,0,1, 0,-convertY2Libh(0));
	
}
