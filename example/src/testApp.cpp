#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	pdf.setup(ofxLibharu::A4, ofxLibharu::LANDSCAPE);
	
	string text = "Kpfx";
	float fontsize = 50;
	string fontName = "Helvetica";
	//fontName = ofToDataPath("DejaVuSansMono.ttf");
	float charSpacing = 3;
	float wordSpacing = 3;
	
	float width = pdf.getTextWidth(text,fontName,fontsize,charSpacing,wordSpacing);
	float descent = pdf.getFontDescent(fontName,fontsize);
	float ascent = pdf.getFontAscent(fontName,fontsize);
	float capital = pdf.getFontCapHeight(fontName,fontsize);
	float xheight = pdf.getFontXHeight(fontName,fontsize);
	
	pdf.setFont(fontName);
	//pdf.setTTFontFromFile(fontName);
	//pdf.setTTFontFromFile(ofToDataPath("DejaVuSansMono.ttf"));
	
	pdf.setDPI(50);
	float fx = 20;
	float fy = pdf.getPageSize().y*.5;
	

	pdf.setFillColor(0,0,0);
	pdf.setFontSize(fontsize); //<<< max font size ??? (HPDF_MAX_FONTSIZE hpdf_page_operator.c)
	pdf.setTextLeading(fontsize);
	pdf.setCharSpacing(charSpacing);
	pdf.setWordSpacing(wordSpacing);
	
	pdf.drawText(text, fx,fy);
	

	pdf.setFillType(OF_OUTLINE);
	pdf.setLineWidth(.1);
	pdf.setStrokeColor(255,0,0);
	pdf.drawRectangle(fx,fy,width,-descent);
	pdf.setStrokeColor(0,255,0);
	pdf.drawRectangle(fx,fy,width,-ascent);
	pdf.setStrokeColor(0,0,255);
	pdf.drawRectangle(fx,fy,width,-capital);
	pdf.setStrokeColor(0,255,255);
	pdf.drawRectangle(fx,fy,width,-xheight);
	
	pdf.drawText(text, fx,fy);


	//new page
	pdf.newPage(ofxLibharu::A4, ofxLibharu::LANDSCAPE);
	pdf.resetStyles();
	
	pdf.setTextAlignment(ofxLibharu::ALIGN_RIGHT);
	pdf.setFontSize(5);
	//pdf.setCharSpacing(2); //<-- issues with align right and bounding box
	//pdf.setWordSpacing(3); //<-- issues with align right and bounding box
	pdf.setTextLeading(3);
	pdf.setFillColor(255,0,0);
	text = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
	pdf.drawTextBox(text, 20,40,100,100);
	
	pdf.setStrokeColor(0,0,0);
	pdf.setLineWidth(.2);
	pdf.setFillType(OF_OUTLINE);
	pdf.drawRectangle(20,40,100,100);
	
	pdf.setLineWidth(3);
	pdf.setLineCapStyle(ofxLibharu::LINE_CAP_ROUND);
	pdf.setStrokeColor(255,0,0);
	pdf.drawLine(10,10,200,200);
	
	
	pdf.save("test.pdf", true);
	pdf.openLastSave();
	
	ofExit();
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
