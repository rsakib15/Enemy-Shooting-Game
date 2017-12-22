#include<GL/gl.h>
#include<GL/glut.h>
#include<bits/stdc++.h>
#define SZ 100000
#define SFI(x)              scanf("%d",&x)
#define PFI(x)              printf("%d",x)
#define SSZ(a)              strlen(a)
#define ABS(x)              ((x)<0?-(x):(x))
#define READ()              freopen("output.txt", "r", stdin)
#define WRITE()             freopen("output.txt", "w", stdout)
#define MEM(n,val)          memset((n), val, sizeof(n))
#define FOR(I,J,K)          for(I = J; I < K; I++)
#define REV(I,J,K)          for(I = J; I > K; I--)

using namespace std;

double man=0.1f;
double man_x[SZ];
double man_y[SZ];
double man_vel[SZ];
double man_stat[SZ]={0};
double man_col[SZ];

double shooter_x=0.0f;
double shooter_y=-1.9f;
double shooter_min_x=-1.9f;
double shooter_max_x=1.9f;
double angle=0.0f;

double bullet_x[SZ];
double bullet_y[SZ];
double bullet_vel=0.05f;
int bullet_stat[SZ]={0};
double bullet_vel_x[SZ];
double bullet_vel_y[SZ];

double tip_x[SZ];
double tip_y[SZ];
int bullet=0;

int points=0;
int on=1000;
int frontCount=-1,cnt=0,high=-1;
int game_over=0;
int game_play=0;
int level=1;
int game_level=0;

double mousex;
double mousey;

int mainmenu=1;
int high_score = 0;
int howtoplay=0;
int about = 0;
int life = 3;
int flag=0;
int a=0;

void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void MainMenu(){
    glLineWidth(4);
    glClearColor(0.22, 0.49, 0.5,0.656);
    glColor3f(1.0,1.0,1.0);

    renderBitmapString(-1.7f,-0.0f,GLUT_BITMAP_TIMES_ROMAN_24,"SHOOTING GAME");

    glBegin(GL_LINES);
        glVertex2f(0.3f,0.7f);
        glVertex2f(0.3f,1.0f);
        glVertex2f(0.3f,0.7f);
        glVertex2f(1.5f,0.7f);
        glVertex2f(0.3f,1.0f);
        glVertex2f(1.5f,1.0f);
        glVertex2f(1.5f,0.7f);
        glVertex2f(1.5f,1.0f);
	glEnd();

	renderBitmapString(0.5f,0.8f,GLUT_BITMAP_TIMES_ROMAN_24,"NEW GAME");

    glBegin(GL_LINES);
        glVertex2f(0.3f,0.3f);
        glVertex2f(0.3f,0.6f);
        glVertex2f(0.3f,0.3f);
        glVertex2f(1.5f,0.3f);
        glVertex2f(0.3f,0.6f);
        glVertex2f(1.5f,0.6f);
        glVertex2f(1.5f,0.3f);
        glVertex2f(1.5f,0.6f);
	glEnd();

	renderBitmapString(0.5f,0.4f,GLUT_BITMAP_TIMES_ROMAN_24,"HIGH SCORE");

	glBegin(GL_LINES);
        glVertex2f(0.3f,-0.1f);
        glVertex2f(0.3f,0.2f);
        glVertex2f(0.3f,-0.1f);
        glVertex2f(1.5f,-0.1f);
        glVertex2f(0.3f,0.2f);
        glVertex2f(1.5f,0.2f);
        glVertex2f(1.5f,-0.1f);
        glVertex2f(1.5f,0.2f);
	glEnd();

	renderBitmapString(0.5f,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,"HOW TO PLAY");

	glBegin(GL_LINES);
        glVertex2f(0.3f,-0.5f);
        glVertex2f(0.3f,-0.2f);
        glVertex2f(0.3f,-0.5f);
        glVertex2f(1.5f,-0.5f);
        glVertex2f(0.3f,-0.2f);
        glVertex2f(1.5f,-0.2f);
        glVertex2f(1.5f,-0.5f);
        glVertex2f(1.5f,-0.2f);
	glEnd();

	renderBitmapString(0.5f,-0.4f,GLUT_BITMAP_TIMES_ROMAN_24,"ABOUT");

	glBegin(GL_LINES);
        glVertex2f(0.3f,-0.9f);
        glVertex2f(0.3f,-0.6f);

        glVertex2f(0.3f,-0.9f);
        glVertex2f(1.5f,-0.9f);

        glVertex2f(0.3f,-0.6f);
        glVertex2f(1.5f,-0.6f);

        glVertex2f(1.5f,-0.9f);
        glVertex2f(1.5f,-0.6f);
	glEnd();

	renderBitmapString(0.5f,-0.8f,GLUT_BITMAP_TIMES_ROMAN_24,"EXIT");
}

void drawBullet(){
	glPushMatrix();
        glTranslatef(-170/1200,220/800,0);
        glutSolidSphere(0.03,50,50);
    glPopMatrix();
}

void drawMan(){
	int i;
    if(frontCount==-1){
        cnt=0;
    }
    if(frontCount==0){
        cnt=1;
    }
	if(frontCount<100000){
		for(i=0;cnt<=2;i++){
			if(i>frontCount || man_y[i]<=-5.0f){
                man_x[i]=((rand()%100)*1.0f/100.0)+((rand()%4)*1.0f)-2;
                man_y[i]=2.3f;
				man_vel[i]=.003f + 3*((rand()%10*1.0f)/10000);
				man_stat[i]=0;
				man_col[i]=rand()%3;
				frontCount++;
				cnt++;
			}
		}
	}
}

void drawMan(int i){
	glColor3f(0.0,0.0,0.0);

    glPushMatrix();
        glTranslatef(0.0,0.07,0.0);
        glutSolidSphere(0.04,50,50);
    glPopMatrix();

    glLineWidth(5);
    glColor3f(0.9,0.0,0.7);

    glBegin(GL_LINES);
        glVertex2f(-0.02,-0.05);
        glVertex2f(-0.09,-0.14);
        glVertex2f(0.02,-0.05);
        glVertex2f(0.09,-0.14);
    glEnd();

    glColor3f(0.9,0.3,0.7);
    glLineWidth(5);

    glBegin(GL_LINES);
        glVertex2f(-0.04,0.01);
        glVertex2f(-0.1,-0.04);
        glVertex2f(0.04,0.01);
        glVertex2f(0.1,-0.04);
    glEnd();

    glColor3f(0.0,1.0,0.7);
    glPointSize(15.0);

    glBegin(GL_POINTS);
        glVertex2f(-0.000,-0.01);
    glEnd();
}

void gameOver(){
    renderBitmapString(-0.5f,0.7f,GLUT_BITMAP_TIMES_ROMAN_24,"GAME OVER");
    renderBitmapString(-0.5f,0.5f,GLUT_BITMAP_TIMES_ROMAN_24,"SCORE : ");

    char str[80];
	sprintf(str,"%d",points);
	for(int i=0;i<(int)(strlen(str));i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);

    glBegin(GL_LINES);
        glVertex2f(-0.6f,-0.5f);
        glVertex2f(-0.6f,-0.2f);
        glVertex2f(-0.6f,-0.5f);
        glVertex2f(0.6f,-0.5f);
        glVertex2f(-0.6f,-0.2f);
        glVertex2f(0.6f,-0.2f);
        glVertex2f(0.6f,-0.5f);
        glVertex2f(0.6f,-0.2f);
	glEnd();

	renderBitmapString(-0.2f,-0.4f,GLUT_BITMAP_TIMES_ROMAN_24,"MENU");

    frontCount=-1;
    cnt=0;
    high=-1;
}

void drawShooter(){
    glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
        glVertex2f(-0.2f,-0.2f);
        glVertex2f(0.2f,-0.2f);
        glVertex2f(0.2f,-0.15f);
        glVertex2f(-0.2f,-0.15f);
	glEnd();

	glBegin(GL_POLYGON);
        glVertex2f(-0.1f,-0.5f);
        glVertex2f(0.1f,-0.5f);
        glVertex2f(0.1f,0.16f);
        glVertex2f(-0.1f,0.16f);
	glEnd();

	glBegin(GL_POLYGON);
        glVertex2f(0.1f,-0.15f);
        glVertex2f(0.4f,-0.15f);
        glVertex2f(0.4f,-0.05f);
        glVertex2f(0.1f,-0.05f);
	glEnd();

	glBegin(GL_POLYGON);
        glVertex2f(-0.1f,-0.15f);
        glVertex2f(-0.4f,-0.15f);
        glVertex2f(-0.4f,-0.05f);
        glVertex2f(-0.1f,-0.05f);
	glEnd();

	glBegin(GL_POLYGON);
        glVertex2f(-0.3f,-0.07f);
        glVertex2f(-0.4f,-0.07f);
        glVertex2f(-0.4f,0.15f);
        glVertex2f(-0.3f,0.1f);
	glEnd();

	glBegin(GL_POLYGON);
        glVertex2f(0.3f,-0.07f);
        glVertex2f(0.4f,-0.07f);
        glVertex2f(0.4f,0.15f);
        glVertex2f(0.3f,0.1f);
	glEnd();

	glBegin(GL_POLYGON);
        glVertex2f(-0.1f,0.16f);
        glVertex2f(0.1f,0.16f);
        glVertex2f(0.005f,0.22f);
	glEnd();
}

void new_update(int value){
	for(int i=0;i<=frontCount;i++){
		if(man_y[i]<=-1.6f){
			man_vel[i]=0;
			man_y[i]=-5.0f;
			man_stat[i]=0;
			frontCount--;
			points--;
		}
		if(shooter_x>man_x[i]-0.46f && shooter_x<man_x[i]+0.46f && man_y[i]-0.05f<=-1.7f){
			life--;
		}
		if(life==0){
            game_over=1;
            game_play=0;
            mainmenu=0;
		}
	}

	for(int i=0;i<=high;i++){
		if(bullet_stat[i]==1){
			bullet_x[i]-=bullet_vel_x[i];
			bullet_y[i]+=bullet_vel_y[i];
			tip_x[i]-=bullet_vel_x[i];
			tip_y[i]+=bullet_vel_y[i];
			if(bullet_y[i]>=2.0f){
				bullet_stat[i]=0;
			}
		}
	}

	for(int i=0;i<=frontCount;i++){
		for(int j=0;j<=high;j++){
			if(tip_x[j]>man_x[i]-0.05f && tip_x[j]<man_x[i]+0.05f && tip_y[j]>man_y[i]-0.05f && tip_y[j]<man_y[i]+0.05f && bullet_stat[j]==1){
				man_vel[i]=0;
				man_y[i]=-5.0f;
				man_stat[i]=0;
				frontCount--;
				bullet_stat[j]=0;
				points++;
			}
		}
	}

	for(int i=0;i<=frontCount;i++){
		if(man_y[i]<0.0f && man_stat[i]==0){
			cnt--;
			man_stat[i]=1;
		}
		if(man_y[i]>=-1.85f){
			man_y[i]-=man_vel[i];
		}
	}

	on+=100;
	game_level+=10;

	if(game_level>=10000){
		level++;
		game_level=1;
	}

    glutTimerFunc(10, new_update, 0);
}

void score(){
	glColor3f(1.0f,1.0f,1.0f);
    renderBitmapString(2.2f,1.8f,GLUT_BITMAP_HELVETICA_18,"SCORE :  ");
	char str[80];
	sprintf(str,"%d",points);
	for(int i=0;i<(int)(strlen(str));i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
}

void showLife(){
	glColor3f(1.0f,1.0f,1.0f);
    renderBitmapString(-2.6f,1.8f,GLUT_BITMAP_HELVETICA_18,"LIFE :  ");
	char str[80];
	sprintf(str,"%d",life);
	for(int i=0;i<(int)(strlen(str));i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
}

void storeHighScore(){
    ofstream outfile("output.txt");
    if(points>a){
        outfile<<points<<endl;
    }
    outfile.close();
}

void showHighScore(){
    ifstream infile("output.txt");
    infile>>a;
    infile.close();

    glColor3f(1.0f,1.0f,1.0f);
    renderBitmapString(-0.7f,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,"HIGH SCORE :  ");
	char str[80];
	sprintf(str,"%d",a);
	for(int i=0;i<(int)(strlen(str));i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);

    glBegin(GL_LINES);
        glVertex2f(-0.6f,-0.5f);
        glVertex2f(-0.6f,-0.2f);
        glVertex2f(-0.6f,-0.5f);
        glVertex2f(0.6f,-0.5f);
        glVertex2f(-0.6f,-0.2f);
        glVertex2f(0.6f,-0.2f);
        glVertex2f(0.6f,-0.5f);
        glVertex2f(0.6f,-0.2f);
	glEnd();

	renderBitmapString(-0.2f,-0.4f,GLUT_BITMAP_TIMES_ROMAN_24,"BACK");
}

void howToPlay(){
    glColor3f(1.0f,1.0f,1.0f);
    renderBitmapString(-0.4f,1.7f,GLUT_BITMAP_TIMES_ROMAN_24,"HOW TO PLAY");

    glBegin(GL_LINES);
        glVertex2f(-0.6f,-1.5f);
        glVertex2f(-0.6f,-1.2f);
        glVertex2f(-0.6f,-1.5f);
        glVertex2f(0.6f,-1.5f);
        glVertex2f(-0.6f,-1.2f);
        glVertex2f(0.6f,-1.2f);
        glVertex2f(0.6f,-1.5f);
        glVertex2f(0.6f,-1.2f);
	glEnd();

	renderBitmapString(-2.7f,1.4f,GLUT_BITMAP_HELVETICA_18,"1. Use Left arrow key to move the shooter Left");
	renderBitmapString(-2.7f,1.2f,GLUT_BITMAP_HELVETICA_18,"2. Use Right arrow key to move the shooter Right");
	renderBitmapString(-2.7f,1.0f,GLUT_BITMAP_HELVETICA_18,"3. Press Space to key to Shoot");
	renderBitmapString(-2.7f,0.8f,GLUT_BITMAP_HELVETICA_18,"4. Kill the object and 1 point will be added to the score");
	renderBitmapString(-2.7f,0.6f,GLUT_BITMAP_HELVETICA_18,"5. If object are missed and cross the shooter 1 life be lost");
	renderBitmapString(-2.7f,0.4f,GLUT_BITMAP_HELVETICA_18,"6. Press ESC to exit the game");
	renderBitmapString(-0.2f,-1.4f,GLUT_BITMAP_TIMES_ROMAN_24,"BACK");
}


void showAbout(){
    glColor3f(1.0f,1.0f,1.0f);
    renderBitmapString(-0.2f,1.7f,GLUT_BITMAP_TIMES_ROMAN_24,"ABOUT");
    renderBitmapString(-0.9f,0.7f,GLUT_BITMAP_TIMES_ROMAN_24,"The game is Designed and Developed by");
    renderBitmapString(-0.9f,0.3f,GLUT_BITMAP_HELVETICA_18,"Sakib Rahman -  (13-23054-1)");
    renderBitmapString(-0.9f,0.0f,GLUT_BITMAP_HELVETICA_18,"Samshad Rahman -  (15-28792-2)");

    glBegin(GL_LINES);
        glVertex2f(-0.6f,-1.5f);
        glVertex2f(-0.6f,-1.2f);
        glVertex2f(-0.6f,-1.5f);
        glVertex2f(0.6f,-1.5f);
        glVertex2f(-0.6f,-1.2f);
        glVertex2f(0.6f,-1.2f);
        glVertex2f(0.6f,-1.5f);
        glVertex2f(0.6f,-1.2f);
	glEnd();

	renderBitmapString(-0.2f,-1.4f,GLUT_BITMAP_TIMES_ROMAN_24,"BACK");
}

void initRendering() {
	glEnable(GL_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(1.0f,1.0f,1.0f,0.0f);
}

void handleResize(int w, int h) {
	int winw=w;
	int winh=h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (double)w / (double)h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y){
	if (key == 27) {
		exit(0);
	}
	else if(key==' ' && on>=1000){
		int i;
		for(i=0;i<high;i++){
			if(bullet_stat[i]==0){
				bullet_x[i]=shooter_x;
				bullet_y[i]=shooter_y;
				tip_x[i]=bullet_x[i];
				tip_y[i]=bullet_y[i]+0.2;
				bullet_vel_x[i]=0;
				bullet_vel_y[i]=bullet_vel;
				bullet_stat[i]=1;
				bullet=1;
				break;
			}
		}
		if(bullet==0){
			high++;
			bullet_x[high]=shooter_x;
			bullet_y[high]=shooter_y;
			tip_x[high]=shooter_x;
			tip_y[high]=shooter_y+0.2;
			bullet_vel_x[high]=0;
			bullet_vel_y[high]=bullet_vel;
			bullet_stat[high]=1;
		}
		on=0;
		bullet=0;
	}
}

void getCoord( int x, int y){
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
	winZ=0;
	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	mousex=posX*100/2;
	mousey=(posY*100)/2;
	glutPostRedisplay();
}

void handleKeypress2(int key, int x, int y){
    if (key == GLUT_KEY_LEFT){
        if(shooter_x>shooter_min_x){
            shooter_x-=0.05;
        }
    }
    else if (key == GLUT_KEY_RIGHT){
        if(shooter_x<shooter_max_x){
            shooter_x+=0.05;
        }
    }
}

void handleMouseclick(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && game_play==0 && mainmenu==1){
        getCoord(x,y);
        if(mousex>=0.3 && mousex<=1.5 && mousey>=0.7 && mousey<=1.0){
            game_play=1;
            game_over=0;
        }

        else if(mousex>=0.3 && mousex<=1.5 && mousey>=0.3 && mousey<=0.6){
            mainmenu=0;
            high_score=1;
        }

        else if(mousex>=0.3 && mousex<=1.5 && mousey>=-0.1 && mousey<=0.2){
            mainmenu=0;
            howtoplay=1;
        }

        else if(mousex>=0.3 && mousex<=1.5 && mousey>=-0.5 && mousey<=-0.2){
            mainmenu=0;
            about=1;
        }
        else if(mousex>=0.3 && mousex<=1.5 && mousey>=-0.9 && mousey<=-0.6){
            exit(0);
        }
    }

    else if (button == GLUT_LEFT_BUTTON && game_play==0 && mainmenu==0 && high_score==1){
        getCoord(x,y);
        if(mousex>=-0.6 && mousex<=0.6 && mousey>=-0.5 && mousey<=-0.2){
            mainmenu=1;
            high_score=0;
        }
    }

    else if (button == GLUT_LEFT_BUTTON && game_play==0 && mainmenu==0 && howtoplay==1){
        getCoord(x,y);
        if(mousex>=-0.6 && mousex<=0.6 && mousey>=-1.5 && mousey<=-1.2){
            mainmenu=1;
            howtoplay=0;
        }
    }

    else if (button == GLUT_LEFT_BUTTON && game_play==0 && mainmenu==0 && about==1){
        getCoord(x,y);
        if(mousex>=-0.6 && mousex<=0.6 && mousey>=-1.5 && mousey<=-1.2){
            mainmenu=1;
            about=0;
        }
    }

    else if (button == GLUT_LEFT_BUTTON && game_play==0 && mainmenu==0 && game_over==1){
        getCoord(x,y);
        if(mousex>=-0.6 && mousex<=0.6 && mousey>=-0.5 && mousey<=-0.2){
            mainmenu=1;
            game_over=0;
            storeHighScore();
            life = 3;
            points=0;

        }
    }
}

void drawScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(game_play==0 && mainmenu==1){
		glPushMatrix();
            glTranslatef(0.0f, 0.0f,-5.0f);
            glColor3f(0.0f,0.0f,0.0f);
            MainMenu();
		glPopMatrix();
	}

	else if(game_play==0 && mainmenu==0 && game_over==1){
		glPushMatrix();
            glTranslatef(0.0f, 0.0f,-5.0f);
            glColor3f(0.0f,0.0f,0.0f);
            gameOver();
		glPopMatrix();
	}

	else if(mainmenu==0 && high_score==1 && game_play==0){
        glPushMatrix();
            glTranslatef(0.0f, 0.0f,-5.0f);
            glColor3f(0.0f,0.0f,0.0f);
            showHighScore();
		glPopMatrix();
	}


	else if(mainmenu==0 && howtoplay==1 && game_play==0){
        glPushMatrix();
            glTranslatef(0.0f, 0.0f,-5.0f);
            glColor3f(0.0f,0.0f,0.0f);
            howToPlay();
		glPopMatrix();
	}

	else if(mainmenu==0 && about==1 && game_play==0){
        glPushMatrix();
            glTranslatef(0.0f, 0.0f,-5.0f);
            glColor3f(0.0f,0.0f,0.0f);
            showAbout();
		glPopMatrix();
	}

	else if(mainmenu==0 && game_play==0 && game_over==1){
        glPushMatrix();
            glTranslatef(0.0f, 0.0f,-5.0f);
            glColor3f(0.0f,0.0f,0.0f);
            gameOver();
		glPopMatrix();
	}

	else if(game_over==0 && game_play==1){
		drawMan();
		glPushMatrix();
            glTranslatef(0.0f, 0.0f,-5.0f);
            glColor3f(0.0f, 0.0f, 0.0f);
            for(int i=0;i<=high;i++){
                if(bullet_stat[i]==1){
                    glPushMatrix();
                        glTranslatef(bullet_x[i],bullet_y[i],0.0f);
                        glRotatef(0.0f,0.0f,0.0f,1.0f);
                        glColor3f(0.0f,0.0f,0.0f);
                        drawBullet();
                    glPopMatrix();
                }
            }

            glPushMatrix();
                glTranslatef(shooter_x,shooter_y,0.0f);
                drawShooter();
            glPopMatrix();

            for(int i=0;i<=frontCount;i++){
                glPushMatrix();
                glTranslatef(man_x[i],man_y[i],0.0f);
                if(man_vel[i]!=0)
                    drawMan(i);
                glPopMatrix();
            }
            glPushMatrix();
                glColor3f(1.0f,0.0f,0.0f);
                score();
                showLife();
            glPopMatrix();
        }
        else{
            glPushMatrix();
                glTranslatef(0.0f, 0.0f, -5.0f);
                glColor3f(0.0f, 0.0f, 0.0f);
            glPushMatrix();
            glPushMatrix();
                glColor3f(1.0f,0.0f,0.0f);
            glPopMatrix();
        }
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1200,800);
	glutInitWindowPosition(220,50);
	glutCreateWindow("Enemy Shooting Game");
	initRendering();
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutReshapeFunc(handleResize);
	glutTimerFunc(5, new_update, 0);
	glutMainLoop();
	return 0;
}
