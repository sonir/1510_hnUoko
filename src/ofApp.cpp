#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    metro = new slMetro(INTERVAL);
    
    ag1 = 0; ag1_note =0; ag1_note_active=0;
    ag2 = 7; ag2_note =0; ag2_note_active=0;
    count =0;
    
    
    params.attack = 2200;
    params.decay = 0;
    params.sustain = 1.0;
    params.duration = 1500;
    params.release = 5000;
    adsr1.setup(params);
    adsr2.setup(params);

    params.attack = 6000;
    params.decay = 0;
    params.sustain = 1.0;
    params.duration = 1500;
    params.release = 10000;
    adsr1b.setup(params);
    adsr2b.setup(params);
    
    adsr1.exponential=false;     adsr1b.exponential=true;     adsr2.exponential=false;     adsr2b.exponential=true;
    
    focused1 = &adsr1; focused2 = &adsr2;
    
    sound.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){

    if(metro->alart()){
        if(count==0){
            focused1=&adsr1; focused2=&adsr2;
            ag1 = move(ag1, ag2);
            ag2 = move(ag2, ag1);

            if(ag1==ag2){
                trigger_at_same = true;
                ag1_note=createNote();
                ag2_note=ag1_note+7;
            }else{
                
                ag1_note=createNote();
                ag2_note=createNote();
                
            }
        }
        
         metro->set(0.3+(random.regular()*0.7)*INTERVAL);
        step();
       
    }
    
    synth_param_t s;
    s.vol1=focused1->update();
    s.note1=ag1_note_active;
    s.vol2=focused2->update();
    s.note2=ag2_note_active;
    sound.update(s);


}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255);
    ofNoFill();
    for(int i=0; i<8; i++){

        ofRect(80+(i*120),(ofGetHeight()/2),20,20);
    }

    // draw ag1
    ofRect(80+(ag1*120),(ofGetHeight()/2)+30,20,20);
    // draw ag2
    ofRect(80+(ag2*120),(ofGetHeight()/2)-30,20,20);

    //Draw Timeposition
    ofNoFill();
    ofRect(80+(count*120),(ofGetHeight()/2)-90,20,20);

    
    //draw Light
    ofFill();
    ofSetColor(focused1->update()*255);
    ofRect(80+(ag1*120),(ofGetHeight()/2)+30,20,20);
    
    ofSetColor(focused2->update()*255);
    ofRect(80+(ag2*120),(ofGetHeight()/2)-30,20,20);

    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


//--------------------------------------------------------------
int ofApp::move(int ag_A, int ag_B){
    
    //Ag1 move
    if(ag_A<ag_B){
        
        int num = (int)(random.regular()*4)+1;
        ag_A+=num;
        
        
    }else{
        
        int num = (int)(random.regular()*4)+1;
        ag_A-=num;
        
    }
    
    //Border turnning
    if(ag_A>=GRID_MAX){
        
        int index_num = GRID_MAX-1;
        ag_A = index_num - (ag_A-index_num);
        
    }else if(ag_A<GRID_MIN){
        
        ag_A = ag_A * (-1);
        
    }
    
    return ag_A;
    
}

void ofApp::step(){

    if(trigger_at_same){
        if(count==ag1){
            positionCheck();
        }
    }else{
        positionCheck(count);
    }

    count++;
    
    //RESET
    if(count>=GRID_MAX){
        count =0;
        secondTrigger = false;
        trigger_at_same = false;
    }
}


void ofApp::positionCheck(){
    focused1 = &adsr1b; focused2 = &adsr2b;
    
    focused1->bang();
    focused2->bang();
    ag1_note_active=ag1_note;
    ag2_note_active=ag2_note;
    metro->set(20.0);

}

bool ofApp::positionCheck(int i){
    
    bool flg = false;
    
    if(ag1==i){
        adsr1.bang();
        ag1_note_active=ag1_note;
        flg = true;
    }
    
    if(ag2==i){
        adsr2.bang();
        ag2_note_active=ag2_note;
        flg = true;
    }
    
    return flg;
    
}

int ofApp::createNote(){
    
    int notes[] = {-3,2,4,7,11};
    return notes[random.range(0, 4)]+OCT_OFFSET;
    
}