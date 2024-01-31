#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_RESET "\x1b[0m"
#define AXIS_COLOR "\x1b[38;5;240m"

#define POINT_COLOR "\x1b[48;5;79m"
#define POINT_STR POINT_COLOR" "ANSI_RESET
#define STRIPING_COLOR "\x1b[48;5;233m"


int RESOLUTION_X = 20;
int RESOLUTION_Y = 20;

int orgininal_max_y = 0;
int orgininal_max_x = 0;

/* point struct */
struct point{
    int x;
    int y;
};
struct point points[] = {
    //ex
    {0,100},
    {1,90},
    {2,80},
    {3,70},
    {4,60},
    {5,50},
    {6,40},
    {7,30},
    {8,35},
    {9,40},
    {10,45},
    {11,50},
    {12,55},
    {13,60},
    {14,65},
    {15,70},
    {16,10},
    {17,20},
    {18,30},
    {19,40}
    
};

/* int to string */
char* itos(int num){
    char* str = malloc(sizeof(char) * 10);
    #include <stdio.h> // Include the necessary header file

    sprintf(str, "%d", num);
    return str;
}


/* get max Y value in points */
int get_max_y(){
    int max = 0;
    for(int i = 0; i < sizeof(points) / sizeof(points[0]); i++){
        if(points[i].y > max){
            max = points[i].y;
        }
    }
    return max;
}

/* get max X value in points */
int get_max_x(){
    int max = 0;
    for(int i = 0; i < sizeof(points) / sizeof(points[0]); i++){
        if(points[i].x > max){
            max = points[i].x;
        }
    }
    return max;
}

/* returns a string of n spaces */
char* spaces(int n){
    char* str = malloc(sizeof(char) * (n + 1));
    for(int i = 0; i < n; i++){
        str[i] = ' ';
    }
    str[n] = '\0';

    return str;
}

/* changes large number points/coords onto our small RESOLUTION_X * RESOLUTION_Y bounds 
    - proportional to the max x and y values in points
    - for example:
    1000,1000(highest in the set) and 500,500(lowest in the set)
    would be scaled to 20,20(upper bound) and 0,0(lower bound) respectively
*/
void scale_points(){
    int max_x = get_max_x();
    int max_y = get_max_y();
    for(int i = 0; i < sizeof(points) / sizeof(points[0]); i++){
        //printf("Scaling point %d,%d", points[i].x, points[i].y);
        points[i].x = (points[i].x * RESOLUTION_X) / max_x;
        points[i].y = (points[i].y * RESOLUTION_Y) / max_y;
        //printf(" to %d,%d\n", points[i].x, points[i].y);
    }
}

/*
    A Graph is a 2D array of strings of RESOLUTION_X by RESOLUTION_Y
*/
void graph_f(){

    //init
    printf(INFO"Initalizing graph...\n");
    orgininal_max_x = get_max_x();
    orgininal_max_y = get_max_y();
    int orginial_max_x_len = strlen(itos(orgininal_max_x));
    int orginial_max_y_len = strlen(itos(orgininal_max_y));
    scale_points();
    RESOLUTION_X++;
    RESOLUTION_Y++; // to remain 0 to N inclusive
    char* maxY_str = itos(get_max_y());
    char* maxX_str = itos(get_max_x());
    int maxY_len = strlen(maxY_str);
    int maxX_len = strlen(maxX_str);
    free(maxY_str);
    free(maxX_str);
    char* graph[RESOLUTION_Y][RESOLUTION_X];
    int axis_num_spacing = 5;

    //init::clear graph
    for(int i = 0; i < RESOLUTION_Y; i++){
        for(int j = 0; j < RESOLUTION_X; j++){
            graph[i][j] = " ";
        }
    }

    //populate points
    for(int i = 0; i < sizeof(points) / sizeof(points[0]); i++){
        graph[points[i].y][points[i].x] = POINT_STR;
    }

    //Header
    printf("\n");
    printf("%s[Grapher]", spaces(RESOLUTION_X*3/2));
    // draw graph
    printf("\n");
    for(int i = RESOLUTION_Y-1; i >= 0; i--){
        /* y padding */
        if(i % axis_num_spacing == 0){
            char* n = itos(i*orgininal_max_y/(RESOLUTION_Y-1));
            printf("%s", spaces( orginial_max_y_len- strlen(n)));
            printf("%s%s", n, "|");
            free(n);
        }
        else{
            printf("%s%s", spaces(orginial_max_y_len), "|");
        }
        
        //graph content ( print each character three times (each is 3 wide))
        for(int j = 0; j < RESOLUTION_X; j++){
            //striping
            if(j%2==0)
                printf(STRIPING_COLOR);
            else
                printf(ANSI_RESET);
            for(int k = 0; k < 3; k++)
                printf("%s", graph[i][j]);
        }
        printf(ANSI_RESET"\n");
    }
    //draw x axis
    printf("%s+", spaces(orginial_max_y_len));
    for(int i = 1; i < RESOLUTION_X+1; i++){
        if(i % axis_num_spacing == 0)
            printf("%s", "---");
        else
            printf("---");
    }
    printf("\n%s", spaces(orginial_max_y_len+1));
    for(int i = 0; i < RESOLUTION_X+1; i++){
        if(i % axis_num_spacing == 0)
        {
            char* n = itos(i*orgininal_max_x/(RESOLUTION_X-1));
            printf("%s",n);
            printf("%s", spaces(3-strlen(n)));
            free(n);
        }   
        else
            printf("   ");
    }
    printf("\n\n");
    printf(INFO"Done graphing...\n\n");
}

