#include<windows.h>
#include<iostream>
#include<random>
#include<math.h>
using namespace std;

class item{
   private:
   int x=1;
   int y=1;
   int z=1;
   int r=0;
   int D=0;
   int R=0;
   public:
   item(){};
   void itemin(int a,int d,int c){
        x=a;
        y=d;
        z=c;
        r=x+30;
        D=y+30;
        R=(D-x)/2;
   }
   void itempaint(HDC hdc){
         if(x==1) return;
         Ellipse(hdc,x,y,r,D);
   };
   void itemmovepaint(HDC hdc,int a,int b){
    if(x==1){
        return;
      }
        int s=0;
        int i=0;
        i=y+b;
        i=i%z;
        i=i%2;
        if(i==0){
          i=-5;
        }
        else{
          i=5;
        }
        y=y+i;
        D=D+i;
        s=x+a;
        s=s%z;
        s=s%2;
        if(s==0){
          s=-5;
        }
        else{
          s=5;
        }
        x=x+s;
        r=r+s;
        Ellipse(hdc,x,y,r,D);
        if(x>800||y>800||r<0||D<0){
          itemDelete();
        }
    };
    void itemDelete(){
          r=0;
          x=1;
          y=1;
          z=1;
          D=0;
    }
    int Xreturn(){
      return (x+r)/2;
    };
    int Yreturn(){
      return (y+D)/2;
    };
    int Rreturn(){
      return R;
    };
   };

class me{
   private:
   int x=360;
   int y=720;
   int r=700;
   int D=380;
   int R=10;
   int beam=0;
   public:
   me(){};
   void beamin(){
    beam++;
   }
   int returnbeam(){
    return beam;
   }
   void gobeam(){

   }
   void keyin(int a ,int b){
     x=x+b;
     D=D+b;
     r=r+a;     
     y=y+a;
   };
    void mepaint(HDC hdc){
     Ellipse(hdc,x,r,D,y);
   };
    int Xreturn(){
      return (x+D)/2;
    };
    int Yreturn(){
      return (r+y)/2;
    };
    int Rreturn(){
      return R;
    };
};

class painter{
    private:
      int x=1;
      int y=1;
      int z=1;
      int r=0;
      int D=0;
      int R=0;
    public:
    painter(){}
    void in(int a,int b,int c){
        x=a;
        y=b;
        z=c;
        D=x+y;
        R=(D-x)/2;
    };
    void paint(HDC hdc){
         Ellipse(hdc,x,r,D,y);
    };
    int Xreturn(){
      return (x+D)/2;
    };
    int Yreturn(){
      return (r+y)/2;
    };
    int Rreturn(){
      return R;
    };
    void movepaint(HDC hdc,int a){
      if(x==1){
        return;
      }
        int s=0;
        r=r+5;
        y=y+5;
        s=x+a;
        s=s%z;
        s=s%2;
        if(s==0){
          s=-5;
        }
        else{
          s=5;
        }
        x=x+s;
        D=D+s;
        Ellipse(hdc,x,r,D,y);
        if(r==800){
          r=0;
          x=1;
          y=1;
          z=1;
          D=0;
        }
    };
};

double meter(int a,int b,int c,int d){
  if(a==1) return 0;
  return sqrt(pow(a-c,2)+pow(b-d,2));
};

int check(int a,int b,int c){
  if(a<=b+c) return 1;
  if(a>b+c) return 0;
  return 0;
};

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp){
   HDC hdc;
   PAINTSTRUCT ps;
   RECT rctDimension;
   static random_device rnd;
   static me me;
   static item item[3];
   static painter q[160];
   static mt19937_64 mt(rnd());
   static uniform_int_distribution<> rand1000(1,800);
   static uniform_int_distribution<> rand101(50,150);
   static uniform_int_distribution<> rand48(3,50);
   static int a=0;
   static int b=0;
   static int c=0;
   static int d=0;
   static int p=0;
   static int u=0;
   static int it=0;
   static int ite=0;
   static bool isDead=false;
    int v=0;
    int w=0;

   switch(msg){
    case WM_KEYDOWN:
         if(wp==VK_UP) v=v-3;
         if(wp==VK_DOWN) v=v+3;
         if(wp==VK_LEFT) w=w-3;
         if(wp==VK_RIGHT) w=w+3;
         me.keyin(v,w);
         return 0;
    case WM_DESTROY:
         PostQuitMessage(0);
         return 0;
    case WM_CREATE:
         isDead=false;
         SetTimer(hwnd,1,50,NULL);
         return 0;
    case WM_TIMER:
         if(u>0){
           for(int l=0;l<u;l++){
           double X=meter(me.Xreturn(),me.Yreturn(),q[l].Xreturn(),q[l].Yreturn());
           if(X>0 && !isDead){
            if(check(X,me.Rreturn(),q[l].Rreturn())==1){
             isDead=true;
             int on_button=MessageBox(hwnd,TEXT("You are dead!"),TEXT("messageBOX"),MB_OK);
             SendMessage(hwnd,WM_DESTROY,wp,lp);
            }
           }
           }
         }
         if(ite>0){
           for(int l=0;l<ite;l++){
           double X=meter(me.Xreturn(),me.Yreturn(),item[l].Xreturn(),item[l].Yreturn());
           if(X>0){
            if(check(X,me.Rreturn(),item[l].Rreturn())==1){
              me.beamin();
              item[l].itemDelete();
            }
           }
           }
         }
         GetClientRect(hwnd,&rctDimension);
         a=rand1000(mt);
         d=rand1000(mt);
         b=rand101(mt);
         c=rand48(mt);
         if(a%10==0){
           q[p].in(a,b,c);
         }
         if(a%40==0&&it<3){
          item[it].itemin(a,d,c);
         }
         InvalidateRect(hwnd,NULL,TRUE);
         return 0;
    case WM_PAINT:
         hdc=BeginPaint(hwnd,&ps);
         HGDIOBJ greenBrush=CreateSolidBrush(RGB(0,240,24));
         HGDIOBJ itemBrush=SelectObject(hdc,greenBrush);
         if(a%40==0&&it<3){
          item[it].itempaint(hdc);
          it++;
         }
         if(it>=1){
          for(int l=0;l<ite;l++)
           item[l].itemmovepaint(hdc,a,d);
         }
         SelectObject(hdc,greenBrush);
         DeleteObject(greenBrush);
         HGDIOBJ redBrush=CreateSolidBrush(RGB(240,0,36));
         HGDIOBJ newBrush=SelectObject(hdc,redBrush);
         if(isDead==false){
         me.mepaint(hdc);
         }
         SelectObject(hdc,redBrush);
         DeleteObject(redBrush);
         HGDIOBJ oldBrush=SelectObject(hdc,GetStockObject(BLACK_BRUSH));
         if(a%10==0){
            q[p].paint(hdc);
            p++;
         }
         if(p>=1){
            for(int l=0;l<u;l++){
              q[l].movepaint(hdc,a);
            }
         }
         if(a%10==0&&u<160){
            u++;
         }
         if(p==160){
            p=0;
         }
         if(a%40==0&&ite<3) ite++;
         if(it>=3) it=0;
         SelectObject(hdc, oldBrush);
         EndPaint(hwnd,&ps);
         return 0;
   }
   return DefWindowProc(hwnd,msg,wp,lp);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
                         PSTR lpCmdLine,int nCmdShow){
    HWND hwnd;
    MSG meg;
    WNDCLASS winc;

    winc.style           = CS_HREDRAW | CS_VREDRAW;
    winc.lpfnWndProc     = WndProc;
    winc.cbClsExtra      =winc.cbWndExtra = 0;
    winc.hInstance       =hInstance;
    winc.hIcon           =LoadIcon(NULL,IDI_APPLICATION);
    winc.hCursor         =LoadCursor(NULL, IDC_ARROW);
    winc.hbrBackground   =(HBRUSH)GetStockObject(WHITE_BRUSH);
    winc.lpszMenuName    =NULL;
    winc.lpszClassName   =TEXT("GAME");

    if(!RegisterClass(&winc)) return 0;

    hwnd=CreateWindow(
        TEXT("GAME") , TEXT("GAMEFACE"),
        WS_OVERLAPPED | WS_VISIBLE,
        0,0,
        800,800,
        NULL,NULL,hInstance,NULL
    );

    if(hwnd==NULL)return 0;

    while(GetMessage(&meg,NULL,0,0))DispatchMessage(&meg);
    return meg.wParam;
                         }