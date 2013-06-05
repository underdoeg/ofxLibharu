#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	pdf.setup(ofxLibharu::A4, ofxLibharu::LANDSCAPE);
	
	string text = "libH.pdf";
	float fontsize = 40;
	//string fontName = "Courier";
	string fontName = ofToDataPath("DejaVuSansMono.ttf");
	//string fontName = ofToDataPath("TSTARMonRouBol.ttf");
	//string fontName = ofToDataPath("SimLt___D.ttf");
	float charSpacing = 1.5;
	float wordSpacing = 0;
	
	float width = pdf.getTextWidth(text,fontName,fontsize,charSpacing,wordSpacing);
	float descent = pdf.getFontDescent(fontName,fontsize);
	float ascent = pdf.getFontAscent(fontName,fontsize);
	float capital = pdf.getFontCapHeight(fontName,fontsize);
	float xheight = pdf.getFontXHeight(fontName,fontsize);
	
	//pdf.setFont(fontName);
	pdf.setTTFontFromFile(fontName);
	
	
	// FONT INFOS
	float fx = 20;
	float fy = fontsize+10;
	
	pdf.setFillColor(0,0,0);
	pdf.setFontSize(fontsize);
	pdf.setCharSpacing(charSpacing);
	pdf.setWordSpacing(wordSpacing);
	
	pdf.drawText(text, fx,fy);
	
	/*float width = pdf.getTextWidth(text);
	float descent = pdf.getFontDescent();
	float ascent = pdf.getFontAscent();
	float capital = pdf.getFontCapHeight();
	float xheight = pdf.getFontXHeight();*/

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
	
	//TEXT BOX
	pdf.setTextAlignment(ofxLibharu::ALIGN_RIGHT);
	
	fontsize = 3;
	float textleading = 5;
	
	pdf.setFontSize(fontsize);
	pdf.setTextLeading(textleading);
	pdf.setFillColor(0,0,0);
	text = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
	
	float tbx=20,tby=100;
	float tbWidth = 100;
	float tbHeight = pdf.getTextBoxHeight(tbWidth,text,fontName,fontsize,textleading,charSpacing,wordSpacing);
		
	pdf.setStrokeColor(255,0,0);
	pdf.setLineWidth(.1);
	pdf.setFillType(OF_OUTLINE);
	pdf.drawRectangle(tbx,tby,tbWidth,tbHeight);
	
	pdf.setLineWidth(.1);
	for(float y=fontsize; y<=tbHeight; y+=textleading){
		pdf.drawLine(tbx,tby+y,tbx+tbWidth,tby+y);
	}
	
	pdf.drawTextBox(text, tbx,tby,tbWidth,tbHeight);
	
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
