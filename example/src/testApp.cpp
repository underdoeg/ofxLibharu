#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	pdf.setup();
	
	pdf.setFontSize(5);
	pdf.setFont("Helvetica");
	
	
	pdf.setTextAlignment(ofxLibharu::ALIGN_RIGHT);
	//pdf.setCharSpacing(1); <-- issues with align right and bounding box
	pdf.setWordSpacing(3);
	pdf.setTextLeading(3);
	pdf.setFillColor(255,0,0);
	string text = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
	pdf.drawTextBox(text, 20,40,100,100);
	
	pdf.setStrokeColor(0,0,0);
	pdf.setLineWidth(.2);
	pdf.setFillType(OF_OUTLINE);
	pdf.drawRectangle(20,40,100,100);
	
	pdf.setLineWidth(3);
	pdf.setLineCapStyle(ofxLibharu::LINE_CAP_ROUND);
	pdf.setStrokeColor(255,0,0);
	pdf.drawLine(10,10,200,200);
	
	
	pdf.newPage(ofxLibharu::A5, ofxLibharu::LANDSCAPE);

	pdf.drawText("PAGE2", 20,20);
	
	pdf.setStrokeColor(0,0,0);
	pdf.setLineWidth(.2);
	pdf.setFillType(OF_FILLED);
	pdf.drawEllipse(20,40,10,10);
	
	
	
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
