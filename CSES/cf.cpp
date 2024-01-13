#include<bits/stdc++.h>
using namespace std;

long long dijkstra(long long n, long long x, long long s, long long d, vector<vector<vector<pair<long long, long long>>>>& adj)
{
   vector<vector<long long>>dis(n,vector<long long>(2,1e10));
   dis[s][0]=0;
   dis[s][1]=0;

   priority_queue<vector<long long>,vector<vector<long long>>,greater<vector<long long>>>pq;
   pq.push({0,s,0});
   pq.push({0,s,1}); // cost ,source,mode

   while(!pq.empty())
   {
        auto p=pq.top();
        pq.pop();

        long long u=p[2],m=p[1],cost=p[0];
        
        /// all railways
        for(auto it:adj[m][u])
        { 
             long long v=it.first,money=it.second;

             if(dis[v][m]>dis[u][m]+money)
             {
                dis[v][m]=dis[u][m]+money;
                pq.push({dis[v][m],v,m});
             }

             if(dis[v][1-m]>dis[u][m]+money+x)
             {
                dis[v][1-m]=dis[u][m]+money+x;
                pq.push({dis[v][1-m],v,1-m});
             }
        }
        /// airport shit
        for (auto it : adj[1-m][u])
        {
             long long v = it.first, money = it.second;

             if (dis[v][1-m] > dis[u][1-m] + money)
             {
                dis[v][1-m] = dis[u][1-m] + money;
                pq.push({dis[v][m], v, 1-m});
             }

             if (dis[v][m] > dis[u][1-m] + money + x)
             {
                dis[v][m] = dis[u][1-m] + money + x;
                pq.push({dis[v][m], v,m});
             }
        }
   }

   return min(dis[d][0],dis[d][1]);

}
long long mlong longime(long long n, long long x, long long s, long long d, long long m1, long long m2,
                  vector<vector<long long>> air, vector<vector<long long>> rail)
{
     
      vector<vector<bool>>vis(n,vector<bool>(2,false));
      vector<vector<vector<pair<long long,long long>>>>adj(2,vector<vector<pair<long long,long long>>>(n));
      for (auto &r : rail)
      {
          adj[0][r[0]].push_back({r[1],r[2]});
      }
      for(auto & a:air)
      {
        adj[1][a[0]].push_back({a[1],a[2]});
      }


      // n 0 is rail and n,1 is air
      return dijkstra(n,x,s,d,adj);
}