#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
int countnode=0;
//Node(State)
struct Node
{
    //state at the node
    int state[3][3];
    //the number of misplaced tiles Heuristic
    int misplaced;
    //store manhattan Heuristic
    int manhattan;
    // position of blank in state
    int x, y;
};
vector<Node>path;

//Print function for printing state

void print(int temp[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout<< temp[i][j]<<" ";
        cout<<endl;
    }
}

// Function for Calculating misplace tiles
int computeMisplaced(int initial[3][3], int fin[3][3])
{
    int count = 0;
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        if (initial[i][j] && initial[i][j] != fin[i][j])// if initial state not equal to final and not equal to 0
           count++;
    return count;
}
//Function for calculating Manhattan Distance
int computeManhattan(int initial[3][3], int fin[3][3])
{                   
    int count = 0;
    int tileVal=0, finx=0, finy=0;
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++){
          tileVal = initial[i][j];
          if(tileVal == 0) continue;
          finx = (tileVal-1) / 3;
          finy = (tileVal-1) % 3;
          count = count + abs(finx - i) + abs(finy - j); //if tile at final position,
          // count=count
      }
    return count;
}
struct Comparetor {
    bool operator()(Node const& p1, Node const& p2)
    {
        return p1.misplaced < p2.misplaced;
    }
};
void solver(int initial[3][3],int final[3][3],int X,int Y,int choice)
{
    priority_queue<Node,vector<Node>,Comparetor>q;
    //vector<Node>path;
    if(choice==1)
    {
        //int countnode=0;
        bool boo=true;
    
        struct Node current;
        memcpy(current.state,initial,sizeof(initial));
         current.misplaced=computeMisplaced(current.state,final);
         current.x=X;
        current.y=Y;
        struct Node start;
        memcpy(start.state,initial,sizeof(initial));
         start.misplaced=computeMisplaced(start.state,final);
         start.x=X;
        start.y=Y;
         path.push_back(start);
        while(boo)
        {
            //left
            if((current.x)-1>=0&&current.y>=0)
            {
                current=start;
              int temp;
              temp=current.state[current.x][current.y];
              current.state[current.x][current.y]=current.state[(current.x)-1][current.y];
              current.state[(current.x)-1][current.y]=temp;
             // Node n1.state=current.state;
             Node n1;
              memcpy(n1.state,current.state,sizeof(current.state));
              n1.misplaced=computeMisplaced(n1.state,final);
              n1.x=(current.x)-1;
              n1.y=current.y;
              q.push(n1);
          }
            //Down
          if(current.x>=0&&(current.y)-1>=0)
          {
              current=start;
              int temp;
              temp=current.state[current.x][current.y];
              current.state[current.x][current.y]=current.state[current.x][(current.y)-1];
              current.state[current.x][(current.y)-1]=temp;
              //Node n2.state=current.state;
              Node n2;
              memcpy(n2.state,current.state,sizeof(current.state));
              n2.misplaced=computeMisplaced(n2.state,final);
              n2.x=(current.x);
              n2.y=(current.y)-1;
              q.push(n2);
          }
          //Up
           if(current.x>=0&&(current.y)+1>=0)
          {
              current=start;
              int temp;
              temp=current.state[current.x][current.y];
              current.state[current.x][current.y]=current.state[current.x][(current.y)+1];
              current.state[current.x][(current.y)+1]=temp;
              //Node n3.state=current.state;
              Node n3;
              memcpy(n3.state,current.state,sizeof(current.state));
              n3.misplaced=computeMisplaced(n3.state,final);
              n3.x=(current.x);
              n3.y=(current.y)+1;
              q.push(n3);
          }
          //right
          if((current.x)-1>=0&&current.y>=0)
          {
              current=start;
              int temp;
              temp=current.state[current.x][current.y];
              current.state[current.x][current.y]=current.state[(current.x)+1][current.y];
              current.state[(current.x)+1][current.y]=temp;
              //Node n4.state=current.state;
              Node n4;
              memcpy(n4.state,current.state,sizeof(current.state));
              n4.misplaced=computeMisplaced(n4.state,final);
              n4.x=(current.x)+1;
              n4.y=current.y;
              q.push(n4);
          }

          Node pq=q.top();
          path.push_back(pq);
          while(!q.empty()){
              q.pop();
               countnode++;
          }
          if(pq.misplaced>=start.misplaced)
          {   
              cout<<"Here output ........"<<endl;
              cout<<"Unsuccessful"<<endl;
              cout<<"START STATE:"<<endl;
              print(initial);
              cout<<endl;
              cout<<"FINAL STATE: "<<endl;
              print(final);
              cout<<"Total number of states explored before termination :"<<countnode+1<<endl;
              return;
          }
          else
          {
               start=pq;
              // path.push_back(current);
          }
          if(current.state==final)
          {
              boo=false;
              break;
          }
        }
        cout<<"Here is output....."<<endl;
        cout<<"Unsuccessful"<<endl;
        cout<<"START STATE:"<<endl;
        print(initial);
        cout<<endl;
        cout<<"FINAL STATE: "<<endl;
        print(final);
        cout<<"Total number of states explored before termination :"<<countnode+1<<endl;
        cout<<"Total Number of states of to optimal path :"<<path.size()<<endl;
        cout<<"Here is our optimal path :"<<endl;
        for(int i=0;i<path.size();i++)
        {
           print(path[i].state);
           cout<<"   ---->"<<endl;
        }
        return;

    }
    else if(choice==2)
    {
        //int countnode=0;
        bool boo=true;
    
        struct Node current;
        memcpy(current.state,initial,sizeof(initial));
         current.manhattan=computeManhattan(current.state,final);
         current.x=X;
        current.y=Y;
          struct Node start;
        memcpy(start.state,initial,sizeof(initial));
         start.manhattan=computeManhattan(start.state,final);
         start.x=X;
        start.y=Y;
         path.push_back(current);
        while(boo)
        {
            //left
            if((current.x)-1>=0&&current.y>=0)
            {
              current=start;
              int temp;
              temp=current.state[current.x][current.y];
              current.state[current.x][current.y]=current.state[(current.x)-1][current.y];
              current.state[(current.x)-1][current.y]=temp;
             // Node n1.state=current.state;
             Node n1;
              memcpy(n1.state,current.state,sizeof(current.state));
              n1.manhattan=computeManhattan(n1.state,final);
              n1.x=(current.x)-1;
              n1.y=current.y;
              q.push(n1);
          }
            //Down
          if(current.x>=0&&(current.y)-1>=0)
          {
              current=start;
              int temp;
              temp=current.state[current.x][current.y];
              current.state[current.x][current.y]=current.state[current.x][(current.y)-1];
              current.state[current.x][(current.y)-1]=temp;
              //Node n2.state=current.state;
              Node n2;
              memcpy(n2.state,current.state,sizeof(current.state));
              n2.manhattan=computeManhattan(n2.state,final);
              n2.x=(current.x);
              n2.y=(current.y)-1;
              q.push(n2);
          }
          //Up
           if(current.x>=0&&(current.y)+1>=0)
          {
              current=start;
              int temp;
              temp=current.state[current.x][current.y];
              current.state[current.x][current.y]=current.state[current.x][(current.y)+1];
              current.state[current.x][(current.y)+1]=temp;
              //Node n3.state=current.state;
              Node n3;
              memcpy(n3.state,current.state,sizeof(current.state));
              n3.manhattan=computeManhattan(n3.state,final);
              n3.x=(current.x);
              n3.y=(current.y)+1;
              q.push(n3);
          }
          //right
          if((current.x)-1>=0&&current.y>=0)
          {
              current=start;
              int temp;
              temp=current.state[current.x][current.y];
              current.state[current.x][current.y]=current.state[(current.x)+1][current.y];
              current.state[(current.x)+1][current.y]=temp;
              //Node n4.state=current.state;
              Node n4;
              memcpy(n4.state,current.state,sizeof(current.state));
              n4.manhattan=computeManhattan(n4.state,final);
              n4.x=(current.x)+1;
              n4.y=current.y;
              q.push(n4);
          }

          Node pq=q.top();
          path.push_back(pq);
          while(!q.empty()){
              q.pop();
               countnode++;
          }
          if(pq.misplaced<=start.misplaced)
          {   
              cout<<"Here output ........"<<endl;
              cout<<"Unsuccessful"<<endl;
              cout<<"START STATE:"<<endl;
              print(initial);
              cout<<endl;
              cout<<"FINAL STATE: "<<endl;
              print(final);
              cout<<"Total number of states explored before termination :"<<countnode+1<<endl;
              return;
          }
          else
          {
               start=pq;
              // path.push_back(current);
          }
          if(current.state==final)
          {
              boo=false;
              break;
          }
        }
        cout<<"Here is output....."<<endl;
        cout<<"Unsuccessful"<<endl;
        cout<<"START STATE:"<<endl;
        print(initial);
        cout<<endl;
        cout<<"FINAL STATE: "<<endl;
        print(final);
        cout<<"Total number of states explored before termination :"<<countnode+1<<endl;
        cout<<"Total Number of states of to optimal path :"<<path.size()<<endl;
        cout<<"Here is our optimal path :"<<endl;
        for(int i=0;i<path.size();i++)
        {
           print(path[i].state);
           cout<<"   ---->"<<endl;
        }
        return;
    }
    

}
int main()
{
    int initial[3][3] = //if default  chosen this will  be initial state
    {   {8, 6, 7},
        {2, 5, 4},
        {3, 0, 1}
    };
    int Choice;
    // Input for matrix
    
    cout<< "Enter 1 to use a default puzzle, or 2 to enter your own puzzle :"<<endl;
    
    cin>>Choice;
    if(Choice == 2){
      cout<<"Please enter the numbers for each row and press enter"<<endl;
      cout<<"Note use 0 for blank."<<endl;
      for(int i = 0; i < 3 ; i++){
        cout<<"Enter Space seprated elements of the row "<<i+1<<endl;
        for(int j = 0; j < 3 ; j++){
          cin>>initial[i][j];
        }
      }
    }
    cout<<"The Entered Matrix is..."<<endl;
    print(initial);
    cout<<endl;

    // Input for Algorithm
    cout<<"choose the Huristic Function"<<endl;
    cout<<"1. Hill climbing with misplaced tile"<<endl;
    cout<<"2. Hill climbing with Manhattan distance"<<endl;
    cin>>Choice;
    cout<<endl;;

    // Defining goal state
    int fin[3][3] =
    {   {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}
    };

    //find the postion of blank in initial
    int x,y;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if(initial[i][j]==0){
          x = i; y = j;
        }
      }
    }
    //Calculating the time
     auto start = high_resolution_clock::now();
    solver(initial,fin,x,y,Choice);
     auto stop = high_resolution_clock::now();
     auto duration = duration_cast<microseconds>(stop - start);
  
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    return 0;
}