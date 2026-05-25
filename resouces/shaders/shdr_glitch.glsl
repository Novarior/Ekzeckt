/* Signed distance drawing methods */
#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform vec2 u_coord;
uniform float u_time;

uniform sampler2D u_texture;
uniform sampler2D u_texture_0;
uniform sampler2D u_texture_1;

#define PI_TWO 1.570796326794897
#define PI 3.141592653589793
#define TWO_PI 6.283185307179586

#define rx vec2(1./min(u_resolution.x,u_resolution.y))
#define duv vec2(gl_FragCoord.xy/u_resolution.xy)

float rand(){
    return fract(sin(u_time)*1e4);
}

vec4 mainImage(vec4 fragColor,vec4 fragCoord){
    vec2 uv=duv;
    vec2 uvR=uv;
    vec2 uvB=uv;
    
    uvR.x=uv.x*1.-rand()*.02*.8;
    uvB.y=uv.y*1.+rand()*.02*.8;
    
    //
    if(uv.y<rand()&&uv.y>rand()-.1&&sin(u_time)<0.){
        uv.x=(uv+.02*rand()).x;
    }
    //
    vec4 c;
    vec2 zero=vec2(1.1,1.1);
    c.r=texture2D(u_texture_0,uvR).r;
    c.g=texture2D(u_texture_0,uv).g;
    c.b=texture2D(u_texture_0,uvB).b;
    c.a=texture2D(u_texture_0,uv).a;
    //
    float scanline=sin(uv.y*800.*rand())/30.;
    c*=1.-scanline;
    
    //vignette
    float vegDist=length((.5,.5)-uv);
    c*=1.-vegDist*.6;
    
    return c;
}

void main(){
    gl_FragColor=mainImage(gl_FragColor,gl_FragCoord);
}
