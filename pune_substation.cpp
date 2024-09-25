#include<bits/stdc++.h>
using namespace std;

vector<pair<int,int>> adj[100];
#define pb push_back
map<string,int>mp;
map<int,string>i2s;
int sz;
vector<string>keys;
void addEdge(string a,string b,int dis){
    int x=mp[a];
    int y=mp[b];
    adj[x].pb({y,dis});
    adj[y].pb({x,dis});
}

void Create_Metro_map(){
    keys.pb("1PCMC");
    keys.pb("2sant tukaram nagar");
    keys.pb("3Bhosari[nashik Phata]");
    keys.pb("4Kasarwadi");
    keys.pb("5Phugewadi");
    keys.pb("6Dapodi");
    keys.pb("7Bopodi");
    keys.pb("8Range Hill Depot");
    keys.pb("9Shivaji Nagar");
    keys.pb("10District Court");
    keys.pb("11Budhwar Peth");
    keys.pb("12Mandai");
    keys.pb("13Hill View park Car Depot");
    keys.pb("14Vanaz");
    keys.pb("15SAnand Nagar");
    keys.pb("16Ideal Colony");
    keys.pb("17Nal stop");
    keys.pb("18Bund Garden");
    keys.pb("19Deccan Gymkhana");
    keys.pb("20Ruby Hall");

    for(int i=0;i<keys.size();i++){
        mp[keys[i]]=i;
        i2s[i]=keys[i];
    }
    sz=keys.size();
    addEdge("1PCMC", "2sant tukaram nagar", 8);
    addEdge("2sant tukaram nagar", "3Bhosari[nashik Phata]", 10);
    addEdge("3Bhosari[nashik Phata]", "5Phugewadi", 8);
    addEdge("3Bhosari[nashik Phata]", "4Kasarwadi", 6);
    addEdge("4Kasarwadi", "6Dapodi", 9);
    addEdge("6Dapodi", "7Bopodi", 7);
    addEdge("7Bopodi", "8Range Hill Depot", 6);
    addEdge("9Shivaji Nagar", "10District Court", 15);
    addEdge("10District Court", "14Vanaz", 6);
    addEdge("14Vanaz", "4Kasarwadi", 7);
    addEdge("4Kasarwadi", "13Hill View park Car Depot", 1);
    addEdge("13Hill View park Car Depot", "12Mandai", 2);
    addEdge("12Mandai", "11Budhwar Peth", 5);
    addEdge("13Hill View park Car Depot", "15SAnand Nagar", 2);
    addEdge("15SAnand Nagar", "16Ideal Colony", 7);
    addEdge("16Ideal Colony", "17Nal stop", 8);
    addEdge("6Dapodi", "18Bund Garden", 2);
    addEdge("20Ruby Hall", "18Bund Garden", 2);
    addEdge("20Ruby Hall", "19Deccan Gymkhana", 3);
    //cout<<"\n*****************************************************************************\n";
    
    return;
}

void displaystations(){
    
    for(int i=0;i<keys.size();i++){
        cout<<i+1<<". "<<keys[i]<<endl;
        
    }
    
}
vector<int>metro_map;
void dfs(int src,int par,vector<bool>&vis){
    vis[src]=1;
    metro_map.pb(src);
    for(auto x:adj[src]){
        if(!vis[x.first]){
            dfs(x.first,src,vis);
        }
    }
}
void displaymap(){
    vector<bool>vis(sz);
    dfs(0,-1,vis);
    for(int i=0;i<metro_map.size();i++){
        if(i!=metro_map.size()-1){
            cout<<i2s[metro_map[i]]<<"=> ";
        }
        else{
            cout<<i2s[metro_map[i]];
        }
    }
    cout<<endl;
}

int shortestdistance(int src,int dest){
    vector<int>dist(sz,INT_MAX);
    dist[src]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    pq.push({src,0});
    while(!pq.empty()){
        auto x=pq.top();
        pq.pop();
        int dis=x.second;
        for(auto y:adj[x.first]){
            int vertex=y.first;
            int dis_ver=y.second;
            if(dist[vertex]>dis+dis_ver){
                dist[vertex]=dis+dis_ver;
                pq.push({vertex,dist[vertex]});
            }
        }
    }
    return dist[dest];
}

void bfs(vector<int>parent[],int src){
    vector<int>dist(sz,INT_MAX);
    queue<int>q;
    q.push(src);
    parent[src]={-1};
    dist[src]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto x:adj[u]){
            int v=x.first;
            int dis_v=x.second;
            if(dist[v]>dist[u]+dis_v){
                dist[v]=dist[u]+1;
                q.push(v);
                parent[v].clear();
                parent[v].push_back(u);
            }
            else if(dist[v]==dist[u]+dis_v){
                parent[v].push_back(u);
            }
        }
    }
}

void find_paths(vector<vector<int>>& paths,vector<int>& path,vector<int> parent[],int u){
    if(u==-1){
        paths.pb(path);
        return;
    }
    for(auto par:parent[u]){
        path.pb(u);
        find_paths(paths,path,parent,par);
        path.pop_back();
    }
}

void printpath(int src,int dest){
    vector<vector<int>>paths;
    vector<int>path;
    vector<int>parent[sz];

    bfs(parent,src);
    find_paths(paths,path,parent,dest);

    for(auto v:paths){
        reverse(v.begin(),v.end());
        for(int u:v){
            cout<<i2s[u]<<" => ";
        }
        cout<<endl;
        break;
    }
}

int main(){
    //displaystations();
    Create_Metro_map();

    cout<<"\n\t\t\t****WELCOME TO THE METRO APP*****\n";
    while(true){
        cout<<"\t\t\t\t~~LIST OF ACTIONS~~\n\n";
        cout<<("1. LIST ALL THE STATIONS IN THE MAP\n");
        cout<<("2. SHOW THE METRO MAP\n");
        cout<<("3. GET SHORTEST DISTANCE FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n");
        cout<<("4. GET SHORTEST TIME TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n");
        cout<<("5. GET SHORTEST PATH TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n");
        cout<<("6. EXIT THE MENU\n\n");
        cout<<("\nENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 6) : \n");
        int choice;
        cin>>choice;
        if(choice==1){
            displaystations();
        }
        else if(choice==2){
            displaymap();
        }
        else if(choice==3){
            cout<<"Enter the serial no. of Source and Destination"<<endl;
            displaystations();
            int x,y;
            cin>>x>>y;
            x--;
            y--;
            int p=shortestdistance(x,y);
            cout<<"Shortest distance between source and destination is "<<p<<" KM\n";
        }

        else if(choice==4){
            cout<<"Enter the serial no. of Source and Destination"<<endl;
            displaystations();
            int x,y;
            cin>>x>>y;
            x--;
            y--;
            int p=shortestdistance(x,y);
            cout<<"Shortest distance between source and destination is "<<p<<" Minutes\n";
        }
        else if(choice==5){
            cout<<"Enter the serial no. of Source and Destination"<<endl;
            displaystations();
            int x,y;
            cin>>x>>y;
            x--;
            y--;
            printpath(x,y);
        }
        else{
            break;
        }
    }
}
