#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define X 25
#define Y 5

int route[X],pathcounter,r,p,k,next,b,counter3,counter2,temp;   //user defined global variables

/** Structure Name: Maze
 ** Purpose: Used to store maze information retrieved from file.
 **          The maze is represented in form of a 2D array wrapped in a structure.
 **/
struct Maze
{
    int maze_array[Y][Y];
};

/** Structure Name: Graph
 ** Purpose: Used to store the Graph constructed by the buildGraph() function.
 **          The graph is represented in form of a 2D array wrapped in a structure.
 **/
struct Graph
{
    _Bool graph_array[X][X];
};

/** Structure Name: Path_Array
 ** Purpose: Used to store the final path Array constructed by the findPath() function.
 **          The path is represented in form of a 1D array wrapped in a structure.
 **/
struct Path_Array
{
	int path[X];
};

/** Function Name: init_path()
 ** Input: None
 ** Output: Returns a Path_Array structure in which all elements of array are initialized to -1
 ** Example Call: struct Path_Array path = init_path();
 **/
struct Path_Array init_path()
{
	struct Path_Array path;
	for(int i = 0; i < X; i++)
		path.path[i] = -1;
	return path;
}
/** Function Name: buildGraph()
 ** Input: Accepts a Maze structure as input
 ** Output: Returns a Graph structure as output
 ** Purpose: Constructs a adjacency matrix graph using the maze information passed as argument
 ** Example Call: struct Graph matrix = buildGraph(maze);
 **/

struct Graph buildGraph(struct Maze maze)
{
    struct Graph adj_matrix;

    for(p=0;p<X;p++)
        for(r=0;r<X;r++)
           adj_matrix.graph_array[p][r] = 0 ;    //initializing the adjacency matrix with 0
    int x=0, aa ;
    for(p=0;p<Y;p++)
      for(r=0;r<Y;r++)
      {
          aa = maze.maze_array[p][r] ;
            for(k=3; k>=0||aa>0;aa/=2)
            {
                if(aa%2==0)
                    {
                         switch(k)
                            { case 0 : adj_matrix.graph_array[x][x-1] = 1 ;     //if left side is open
                                break ;
                              case 1 : adj_matrix.graph_array[x][x+5] = 1 ;     //if down side is open
                                break ;
                              case 2 : adj_matrix.graph_array[x][x+1] = 1 ;     //if right side is open
                                break ;
                              case 3 : adj_matrix.graph_array[x][x-5] = 1 ;     //if upper side is open
                                break ;
                            }
                    }
            k-- ;
          }
	x++ ;
      }

    return adj_matrix;         //adjancency matrix is calculated
}

/** Function Name: findPath
 ** Input: graph - Graph structure
 **        src - start point of path
 **        dst - end point of path
 ** Output: Returns a Path_Array structure which contains the path in the maze from src to dst.
 ** Example Call: struct Path_Array path = findPath(graph, 0, 24)
 **/

struct Path_Array findPath(struct Graph graph, int start, int finish)
{
    struct Path_Array path = init_path();

    for(p = 0; p < X; p++)
	route[p] = -1;
    pathcounter=0;                         //starting point index
    route[pathcounter]=0;                  //starting point in matrix
    while(route[pathcounter]<finish)     //till it find the destination
    {
       next=-1;
       for(b=0;b<25;b++)
       {
          if(graph.graph_array[route[pathcounter]][b]==1)
    	  {
   	     graph.graph_array[route[pathcounter]][b]=0;
             next=b;
             break;
          }
       }
       if(next!=-1)
       {
          pathcounter++;
          route[pathcounter]=next;
       }
       else
       {
          route[pathcounter]=-1;
          pathcounter--;
       }
    }               //path is been founded

    // ****algo for optimisation of path starts here*****

    counter2=0;
    for(p=0;p<X;p++)
    {
       counter3=0;
       for(r=p+1;r<X;r++)
       {
          if(route[p]==route[r])
          {  counter3=1;
             temp=r;
             break;
          }
      }
      if(counter3==0)
      {
          path.path[counter2]=route[p];
          counter2++;
      }
      if(counter3==1)
      {
	 path.path[counter2]=route[r];
	 p=temp;
	 counter2++;
      }
   }

   return path;       //final path calculated
}

/** Function Name: main_function
 ** Input: maze - Maze structure
 **        start - start point of path
 **        finish - end point of path
 ** Output: Returns a Path_Array structure which contains the path in the maze from start to finish.
 ** Logic: This function first constructs a graph from the maze passed as argument and then finds out
 **        path from start to finish. The path is returned as a Path_Array structure.
 ** Example Call: struct Path_Array path = main_function(maze,0,24);
 **/

struct Path_Array main_function(struct Maze maze, int start, int finish)
{
    struct Graph adjacency_matrix = buildGraph(maze);
    struct Path_Array path = findPath(adjacency_matrix, start, finish);
    return path;
}

/** Function Name: parseFile
 ** Input: fileName -  a string containing the relative path of the test case
 ** Output: Returns a Maze structure.
 ** Logic: This function reads the the specified txt file in the TestCases folder and constructs
           a Maze structure from the information.
 ** Example Call: struct Maze maze = parseFile("..\\..\\Task 1A\\TestCases\\maze_4.txt");
 **/

struct Maze parseFile(char fileName[70])
{
    FILE *fp;
    char buff[100];
    int i = 0, j = 0;
    struct Maze maze;
    fp = fopen(fileName,"r");
    fgets(buff, 100, (FILE*)fp);
    char *token = strtok(buff," ");
    while(token != NULL)
    {
        int temp = atoi(token);
        maze.maze_array[i][j] = temp;
        j++;
        if(j == 5)
        {
            i++;
            j = 0;
        }
        token = strtok(NULL, " ");
    }
    return maze;
}

/**************************************** Utility Functions *********************************/

/** Function Name: coord_to_flat
 ** Input: Accepts coordinates x and y of maze cell as input.
 ** Logic: The maze structure is represented as a 2D array. The cells of the maze can be numbered
 **        in a sequential form (0,1,2,3,4,5....23,24) so that it is easier to construct a graph.
 **        This function accepts the maze cell coordinates and returns an integer.
 ** Output: Returns an integer representing the position of maze cell relative to the start position.
 ** Example Call: coord_to_flat()
 **/
int coord_to_flat(int x, int y)
{
    return x*Y + y;
}

/**************************************** Utility Functions *********************************/
