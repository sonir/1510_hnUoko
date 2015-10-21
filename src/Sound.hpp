//
//  Sound.hpp
//  uoko01
//
//  Created by sonir on 10/21/15.
//
//

#ifndef Sound_hpp
#define Sound_hpp

#define HOST "127.0.0.1"
#define PORT 54321

#include <stdio.h>
#include "ofxOsc.h"

typedef struct synth_param_t {
    
    float vol1;
    int note1;

    float vol2;
    int note2;

    
} synth_param_t;

class Sound {
    
    public:
        Sound(){
            
            
        };
    
        void setup(){
            
            sender.setup(HOST,PORT);
            
        };
    
        void update(synth_param_t param){
            
            ofxOscMessage m;
            m.setAddress("/uoko/update");
            m.addFloatArg(param.vol1);
            m.addFloatArg(param.vol2);

            m.addIntArg(param.note1); //Note
            m.addIntArg(param.note2); //Note
            sender.sendMessage(m);
            
            
        };
    
    
        ofxOscSender sender;

    
    
};

#endif /* Sound_hpp */
