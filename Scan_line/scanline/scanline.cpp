#include <iostream>
#include <List>
#include <vector>
#include <GL/glut.h>
#include <Windows.h>
#include <set>
using namespace std;
#define HEIGHT 700
#define WIDTH 700
#define DRAW_POINT 0
#define DRAW_LINE 1
#define DRAW_FILL 2
void init();
struct Point {
	int x, y;
	Point(int ix, int iy) {
		x = ix;
		y = iy;
	}
};
struct Edge {
	int y_up;
	double x, dx;

    Edge(Point p1, Point p2) {
        y_up = (p1.y > p2.y) ? p1.y : p2.y;
        x = (p1.y > p2.y) ? p2.x : p1.x;
        dx = (double)(p1.x - p2.x) / (double)(p1.y - p2.y);
    }
    Edge(int iy_up, double ix, double idx) {
        y_up = iy_up;
        x = ix;
        dx = idx;
    }
    bool operator < (const Edge edge) const {
        if (x == edge.x) return dx < edge.dx;
        return x < edge.x;
    }
};
int x_click, y_click, windowID;
bool first_click = true;
set<Edge>* AET = new set<Edge>();//平衡二叉树
vector<Edge> edgeTable[HEIGHT];
vector <Point> points;


void fillPolygon() {
    cout << "in fillPolygon()" << endl;
    int UP = points[0].y, DOWN = points[0].y;
    //建立边表
    points.push_back(points[0]);
    for (int i = 1; i < points.size(); i++) {
        UP = (UP < points[i].y) ? points[i].y : UP;
        DOWN = (DOWN > points[i].y) ? points[i].y : DOWN;
        if (points[i].y == points[i - 1].y)
            continue;
        Edge edge(points[i - 1], points[i]);
        int miny = (points[i-1].y < points[i].y) ? points[i-1].y : points[i].y;
        /*auto it = edgeTable[miny].begin();
        while (it!= edgeTable[miny].end()) {
            if (it->x > edge.x) break;
            if (it->x == edge.x && it->dx >= edge.dx) break;
        }
        edgeTable[miny].insert(it, edge);*/
        edgeTable[miny].push_back(edge);
    }


    //扫描线填充
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    for (int y = DOWN; y < UP; y++) {

        for (int i = 0; i < edgeTable[y].size(); i++) {
            AET->insert(edgeTable[y][i]);
        }
        //cout << AET->size() << endl;
        auto it = AET->begin();
        vector<Edge> AETtemp;

        
        while (it != AET->end()) {
            AETtemp.push_back(Edge(it->y_up, it->x + it->dx, it->dx));
            int lx = it->x;
            ++it;
            AETtemp.push_back(Edge(it->y_up, it->x + it->dx, it->dx));
            int rx = it->x;
     
            glVertex2f(lx, HEIGHT - y);
            glVertex2f(rx, HEIGHT - y);
            
            ++it;
        }
        

        AET->clear();
        for (int i = 0; i < AETtemp.size(); i++) {
            if(AETtemp[i].y_up > y+1)
                AET->insert(AETtemp[i]);
        }
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);  
    glFlush();
    
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        points.push_back(Point(x, y));
        printf("%d %d\n", x, y);
        if (first_click) {
            glColor3f(0, 0, 1);
            glBegin(GL_POINTS);
            glVertex2f(x, HEIGHT - y);
            first_click = false;
        }
        else {          
            glColor3f(0, 0, 1);
            glLineWidth(3);
            glBegin(GL_LINES);       
            for (int i = 1; i < points.size(); i++) {
                glVertex2f(points[i - 1].x, HEIGHT - points[i - 1].y);
                glVertex2f(points[i].x, HEIGHT - points[i].y);
            }
        }  
       glEnd();
       glFlush();
    }
}
void keyPress(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_F1:
        fillPolygon();
        break;
    case GLUT_KEY_F2:
        cout << "F2" << endl;  
        glutDestroyWindow(windowID);
        init();
        /*glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glutSwapBuffers();
        UpdateWindow(FindWindow(TEXT("FREEGLUT"), nullptr));*/
        break;
    }
    
}

void init() {
    first_click = true;  
    AET->clear();
    for (int i = 0; i < HEIGHT; i++)  edgeTable[i].clear();
    points.clear();

    int type = 0;
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(400, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    windowID = glutCreateWindow("Scan-Line Filling Polygon");

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);//原点左边改到窗口左下角
    //glPointSize(2.0f);

    glutMouseFunc(mouseClick);
    glutSpecialFunc(keyPress);
    glutDisplayFunc(display);

    glutMainLoop();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
    return 0;
}