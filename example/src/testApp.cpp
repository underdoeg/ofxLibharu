#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	pdf.setup(ofxLibharu::A4, ofxLibharu::LANDSCAPE);
	//pdf.setFont("Helvetica");	
	
	//DRAW FONT DETAILS
	/*pdf.setFillColor(0,0,0);
	pdf.setFontSize(40);
	pdf.setCharSpacing(1.5);
	pdf.setWordSpacing(0);
	
	float fx = 20;
	float fy = 20+pdf.getFontSize();
	
	string text = "libH.pdf";
	pdf.drawText(text, fx,fy);
	
	float width = pdf.getTextWidth(text);
	float descent = pdf.getFontDescent();
	float ascent = pdf.getFontAscent();
	float capital = pdf.getFontCapHeight();
	float xheight = pdf.getFontXHeight();

	pdf.setFillType(OF_OUTLINE);
	pdf.setLineWidth(.1);
	pdf.setStrokeColor(255,0,0);
	pdf.drawRectangle(fx,fy,width,-descent);
	pdf.setStrokeColor(0,255,0);
	pdf.drawRectangle(fx,fy,width,-ascent);
	pdf.setStrokeColor(0,0,255);
	pdf.drawRectangle(fx,fy,width,-capital);
	pdf.setStrokeColor(0,255,255);
	pdf.drawRectangle(fx,fy,width,-xheight);*/
	

	
	//DRAW ROTATED TEXT BOX
	string fontPath = ofToDataPath("SimLt___D.ttf");
	float fontSize = 1;
	float leading = 2;
	float charSpacing = .2;
	float wordSpacing = .2;
	
	pdf.setFont(fontPath);
	pdf.setTextAlignment(ofxLibharu::ALIGN_RIGHT);
	pdf.setFontSize(fontSize);
	pdf.setTextLeading(leading);
	pdf.setCharSpacing(charSpacing);
	pdf.setWordSpacing(wordSpacing);
	pdf.setFillColor(0,0,0);
	
	string text = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
	float tbx = 30,tby = 80;
	float tbWidth = 100;
	//float tbHeight = pdf.getTextBoxHeight(tbWidth,text);
	
	float tbHeight = pdf.getTextBoxHeight(tbWidth,text,fontPath,fontSize,leading,charSpacing,wordSpacing);


	pdf.setStrokeColor(255,0,0);
	pdf.setLineWidth(.1);
	pdf.setFillType(OF_OUTLINE);

	pdf.pushMatrix();
	pdf.rotate(90,tbx+tbWidth*.5,tby+tbHeight*.5);
	pdf.translate(-tbWidth*.5,-tbHeight*.5);
	
	for(float y=pdf.getFontSize(); y<=tbHeight; y+=pdf.getTextLeading()){
		pdf.drawLine(0,y,tbWidth,y);
	}
	pdf.drawRectangle(0,0,tbWidth,tbHeight);
	pdf.drawTextBox(text, 0,0,tbWidth,tbHeight);
	
	pdf.popMatrix();
	
	
	//SAVE PDF
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
