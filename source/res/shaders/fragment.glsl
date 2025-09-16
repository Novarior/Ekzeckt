/* Signed distance drawing methods */
#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform vec2 u_coord;
uniform float u_time;

#define PI_TWO 1.570796326794897
#define PI 3.141592653589793
#define TWO_PI 6.283185307179586
#define MAX_ITER 5

#define rx vec2(1./min(u_resolution.x,u_resolution.y))
#define uv vec2(FragCoord.xy/u_resolution.xy)

vec4 mainImage(vec4 fragColor,vec4 FragCoord)
{
    float time=u_time/PI+TWO_PI;
    
    vec2 p=mod(uv*PI*2.+u_time/PI_TWO,TWO_PI)-350.;
    p+=vec2(uv.x-(2.*u_time),uv.y+(-u_time*.9));
    vec2 i=vec2(p);
    float c=1.;
    float inten=.005;
    float v1,v2;
    vec3 bl_color=vec3(.9059,.8627,.8627);
    vec3 mixc=vec3(.0588,.698,.8745);
    
    for(int n=0;n<MAX_ITER;n++)
    {
        float t=time*(1.-(1.5/float(n+1)));
        i=p+vec2(cos(t-i.x)+sin(t+i.y),sin(t-i.x)+cos(t+i.y));
        v1=p.x/(sin(i.x+t)/inten);
        v2=p.y/(cos(i.y+t)/inten);
        
        c+=1./length(vec2(v1,v2));
    }
    c/=float(MAX_ITER);
    c=1.17-pow(c,1.4);
    vec3 colour=vec3(pow(abs(c),8.));
    colour-=mix(colour,bl_color,1.);
    colour=clamp(colour+mixc,0.,1.);
    
    return vec4(colour,1.);
}
void main(){
    gl_FragColor=mainImage(gl_FragColor,gl_FragCoord);
}
