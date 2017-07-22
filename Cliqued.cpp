 #include <stdio.h>
    #include <stdlib.h>
    #include <limits.h>
    #include <map>
    #include <iostream>
    #include<bits/stdc++.h>
    #define zap(s,u,v) for(s=u;s<=v;s++)
    #define M 1000000000000 
    using namespace std;
     
    #define ll long long 
     
     
     
    struct AdjListNode
    {
        ll dest;
        ll weight;
        struct AdjListNode* next;
    };
     
    struct AdjList
    {
        struct AdjListNode *head;  
    };
     
    struct Graph
    {
        ll V;
        struct AdjList* array;
    };
     
    struct AdjListNode* newAdjListNode(ll dest, ll weight)
    {
        struct AdjListNode* newNode =
                (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
        newNode->dest = dest;
        newNode->weight = weight;
        newNode->next = NULL;
        return newNode;
    }
     
    struct Graph* createGraph(ll V)
    {
        struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
        graph->V = V;
     
        graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
     
         
        for (ll i = 0; i < V; ++i)
            graph->array[i].head = NULL;
     
        return graph;
    }
     
     
    void addEdge(struct Graph* graph, ll src, ll dest, ll weight)
    {
        
        struct AdjListNode* newNode = newAdjListNode(dest, weight);
        newNode->next = graph->array[src].head;
        graph->array[src].head = newNode;
     
    }
     
     
    struct MinHeapNode
    {
        ll  v;
        ll dist;
    };
     
    struct MinHeap
    {
        ll size;      
        ll capacity;  
        ll *pos;     
        struct MinHeapNode **array;
    };
     
     
    struct MinHeapNode* newMinHeapNode(ll v, ll dist)
    {
        struct MinHeapNode* minHeapNode =
               (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
        minHeapNode->v = v;
        minHeapNode->dist = dist;
        return minHeapNode;
    }
     
     
    struct MinHeap* createMinHeap(ll capacity)
    {
        struct MinHeap* minHeap =
             (struct MinHeap*) malloc(sizeof(struct MinHeap));
        minHeap->pos = (ll *)malloc(capacity * sizeof(ll));
        minHeap->size = 0;
        minHeap->capacity = capacity;
        minHeap->array =
             (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
        return minHeap;
    }
     
     
    void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
    {
        struct MinHeapNode* t = *a;
        *a = *b;
        *b = t;
    }
     
     
    void minHeapify(struct MinHeap* minHeap, ll idx)
    {
        ll smallest, left, right;
        smallest = idx;
        left = 2 * idx + 1;
        right = 2 * idx + 2;
     
        if (left < minHeap->size &&
            minHeap->array[left]->dist < minHeap->array[smallest]->dist )
          smallest = left;
     
        if (right < minHeap->size &&
            minHeap->array[right]->dist < minHeap->array[smallest]->dist )
          smallest = right;
     
        if (smallest != idx)
        {
            
            MinHeapNode *smallestNode = minHeap->array[smallest];
            MinHeapNode *idxNode = minHeap->array[idx];
     
            
            minHeap->pos[smallestNode->v] = idx;
            minHeap->pos[idxNode->v] = smallest;
     
            
            swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
     
            minHeapify(minHeap, smallest);
        }
    }
     
     
    ll isEmpty(struct MinHeap* minHeap)
    {
        return minHeap->size == 0;
    }
     
     
    struct MinHeapNode* extractMin(struct MinHeap* minHeap)
    {
        if (isEmpty(minHeap))
            return NULL;
     
        
        struct MinHeapNode* root = minHeap->array[0];
     
        
        struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
        minHeap->array[0] = lastNode;
     
        minHeap->pos[root->v] = minHeap->size-1;
        minHeap->pos[lastNode->v] = 0;
     
        
        --minHeap->size;
        minHeapify(minHeap, 0);
     
        return root;
    }
     
     
    void decreaseKey(struct MinHeap* minHeap, ll v, ll dist)
    {
        
        ll i = minHeap->pos[v];
     
        
        minHeap->array[i]->dist = dist;
     
        
        while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
        {
            minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
            minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
            swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
     
            i = (i - 1) / 2;
        }
    }
     
     
    bool isInMinHeap(struct MinHeap *minHeap, ll v)
    {
       if (minHeap->pos[v] < minHeap->size)
         return true;
       return false;
    }
     
     
    void printArr(ll dist[], ll n,ll src)
    {
        ll sum=0 ;
        for (ll i =1; i < n; ++i)
            printf("%lld ", dist[i]);
            printf("\n");
            
    }
     
     
    void dijkstra(struct Graph* graph, ll src)
    {
        ll V = graph->V;
        ll dist[V];      
     
        
        struct MinHeap* minHeap = createMinHeap(V);
     
       
        for (ll v = 0; v < V; ++v)
        {
            dist[v] =M;
            minHeap->array[v] = newMinHeapNode(v, dist[v]);
            minHeap->pos[v] = v;
        }
     
        minHeap->array[src] = newMinHeapNode(src, dist[src]);
        minHeap->pos[src]   = src;
        dist[src] = 0;
        decreaseKey(minHeap, src, dist[src]);
     
        
        minHeap->size = V;
     
        
        while (!isEmpty(minHeap))
        {
            
            struct MinHeapNode* minHeapNode = extractMin(minHeap);
            ll u = minHeapNode->v; 
     
            struct AdjListNode* pCrawl = graph->array[u].head;
            while (pCrawl != NULL)
            {
                ll v = pCrawl->dest;
     
                if (isInMinHeap(minHeap, v) && dist[u] != M && 
                                              pCrawl->weight + dist[u] < dist[v])
                {
                    dist[v] = dist[u] + pCrawl->weight;
                    decreaseKey(minHeap, v, dist[v]);
                }
                pCrawl = pCrawl->next;
            }
        }
        
        printArr(dist, V,src);
    }
     
     
     
    int main()
    {
        ll t,i,j,k,m,n,s,v,x,p,q,dis  ;
        cin>> t ;
        while(t--)
        {
            cin>> n  ;
            cin>> k  ;
            cin>> x  ;
            cin>> m  ;
            cin>> v  ;
            //printf(" Xa%d ",x);
            struct Graph* graph = createGraph(n+1) ;
           
           for(i=1;i<=m;i++)
           {
               cin>> p;
               cin>> q ;
               cin>> dis ;
              // printf(" Xb%d ",x);
               addEdge(graph, p, q, dis);
               addEdge(graph, q, p, dis);
           }
           for(j=1;j<=k;j++)
               {
                   addEdge(graph, 0, j, x);
                   addEdge(graph, j, 0, 0);
               }
           dijkstra(graph, v);
            
            
        }
     
        return 0;
    }   
