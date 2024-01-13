#include <bits/stdc++.h>
using namespace std;

#define pll pair<long, long>
#define pii pair<int, int>
#define pb push_back
#define ll long long
#define _test     \
    ll _TEST;     \
    cin >> _TEST; \
    while (_TEST--)
class TrieNode
{
public:
    TrieNode *children[26];
    ll count,sum;
    TrieNode()
    {
        for(ll i=0;i<26;i++)
        children[i]=NULL;

        count=sum=0;
    }
};

class Trie
{
public:
    TrieNode *root;
    Trie()
    {
        root = new TrieNode();
    }

    void insert(string &s)
    {
        TrieNode*curr=root;
        curr->count++;
        curr->sum += s.size() ;

        for(ll i=0;i<s.size();i++)
        {
            
            if(!curr->children[s[i]-'a'])
            curr->children[s[i]-'a']=new TrieNode();
            curr=curr->children[s[i]-'a'];

            curr->count++;
            curr->sum += s.size() - i;
        }
        
    }

    ll func(string &s)
    {
        TrieNode*curr=root,*kp=NULL;
        ll ans=0,n=s.size();
        ll prevCount=curr->count,prevSum=curr->sum;
        for(ll i=0;i<n;i++)
        {
            if(!curr->children[s[i]-'a'])
            {
                ans+=prevSum;
                ans+=(prevCount)*(n-i);
                return ans;
            }
            

            curr=curr->children[s[i]-'a'];

            //cout<<curr->count<<" "<<curr->sum<<endl;
            
            
                ans+=prevSum-curr->sum;
                ans+=(prevCount-curr->count)*(n-i);
            

            // cout<<ans<<endl;

            prevSum=curr->sum-curr->count;
            prevCount=curr->count;
        }
        
        return ans+prevSum;
    }
};

void work()
{
    Trie t;

    ll n;
    cin>>n;
    
    vector<string>v(n);
    for(ll i=0;i<n;i++)
    {
        string s;
        cin>>s;

        t.insert(s);
        reverse(s.begin(),s.end());

        v[i]=s; 
        
    }
    

    ll ans=0;

    for(ll i=0;i<n;i++)
    {
         ll x=t.func(v[i]);
         ans+=x;
    }

    cout<<ans<<"\n";



}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // _test
    // {
        work();
    //}
}