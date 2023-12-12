#include <bitset>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

std::vector<long long> SieveOfEratosthenes(long long n)
{
    std::vector<long long> answer;
    long long* Primes = new long long[30000000];
    Primes[0] = 1;
    for (long long i = 3; i*i <= n; i += 2) {
        if (Primes[i / 2] == 0) {
            for (long long j = 3 * i; j <= n; j += 2 * i)
                Primes[j / 2] = 1;
        }
    }
    for (long long i = 1; i <= n; i++) {
        if (i == 2)
            answer.push_back(i);
        else if (i % 2 == 1 && Primes[i / 2] == 0)
            answer.push_back(i);
    }
    return answer;
}


class priority_heap{
private:
    std::vector<std::pair<long long,long long>> heap;
    void swiftUP(long long i)
    {
        while (i > 0 && heap[(i-1)/2].first > heap[i].first) {
            std::swap(heap[(i-1)/2], heap[i]);
            i = (i-1)/2;
        }
    }
    void swiftDOWN(long long i)
    {
        long long swapIndex = i;
        if (i*2 + 1< heap.size() && heap[i*2 + 1].first < heap[swapIndex].first) {
            swapIndex = i*2 + 1;
        }
        if (i*2 + 2 < heap.size() && heap[i*2 + 2].first < heap[swapIndex].first) {
            swapIndex = i*2 + 2;
        }
        if (i != swapIndex) {
            std::swap(heap[i], heap[swapIndex]);
            swiftDOWN(swapIndex);
        }
    }
public:
    priority_heap(std::vector<long long>& host1){
        heap.resize(host1.size());
        for(long long i=0;i<host1.size();i++){
            heap[i].first=host1[i];
            heap[i].second=host1[i];
        }
        for(long i=heap.size()/2-1;i>=0;--i){
            swiftDOWN(i);
        }
    }
    void insert(long long data,long long id){
        heap.push_back(std::make_pair(data,id));
        swiftUP(heap.size()-1);
    }
    std::pair<long long,long long> extract_max(){
        std::pair<long long,long long>  result = heap[0];
        heap[0] = heap[heap.size()-1];
        heap.pop_back();
        swiftDOWN(0);
        return result;
    }
    long long top_id(){
        return heap[0].second;
    }
    void delete_element(long long id){
        long long i=0;
        while(heap[i].second!=id)++i;
        heap[i]=heap[heap.size()-1];
        if(i!=heap.size()-1)heap.pop_back();
        if(heap[(i-1)/2] < heap[i])
            swiftUP(i);
        else
            swiftDOWN(i);
    }
    bool empty(){
        return heap.size()==0;
    }
};





int main()
{
    long long n;
    std::cin>>n;
    std::vector<long long> prime= SieveOfEratosthenes(30000000);


    priority_heap priorityHeap(prime);
    std::vector<long long> answer;

    while(n--){
        std::pair<long long,long long> buffer = priorityHeap.extract_max();
        long long ret=buffer.first;
        if(ret==buffer.second)answer.push_back(buffer.second);
        else {
            while (ret != buffer.second) {
                answer.push_back(buffer.second);
                answer.push_back(buffer.second);
                ret = sqrt(ret);
            }
        }
        priorityHeap.insert(buffer.first*buffer.first,buffer.second);
    }
    sort(answer.begin(),answer.end());
    std::cout<<answer.size()<<"\n";
    for(long long i:answer){
        std::cout<<i<<" ";
    }

    return 0;
}