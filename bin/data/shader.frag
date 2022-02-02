#version 150

uniform vec2 resolution;
uniform float time;
uniform vec2 flow;
uniform float vol;
in vec4 coordVarying;
out vec4 outputColor;

void main()
{
    //中心を(0,0)にし，画面の縦横比を揃える
    vec2 p=(2.0*gl_FragCoord.xy-resolution)/min(resolution.x,resolution.y);
    
    //iの数だけ滑らかになる
    for(float i=1.;i<30.;i++)
    {
        //.5 細かさ
        p.x += .5/i*sin(i*p.y+time)+1.;
        p.y += .5/i*cos(i*p.x+time)+1.;
    }
    
    //動体検知した値を追加していく
    //p.x += flow.x*5.;
    //p.y += flow.y*5.;
    
    
    
    vec3 col=vec3(abs(sin(1.0*(p.x+p.y))),  abs(sin(1.0*(p.x+p.y))), abs(sin(1.0*(p.x+p.y))));
    outputColor=vec4(col, vol);
}
