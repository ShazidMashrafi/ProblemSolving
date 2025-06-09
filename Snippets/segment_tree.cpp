class SegmentTree
{
vector<int>segment;
public:
 SegmentTree(int sz){
  segment.resize(4*sz + 1);
 }
 // Build Segement Tree
 void build(int ind , int low , int high  , vector<int> &v ){
  if(low == high){
   segment[ind] = v[low];
   return;
  }
  int mid = (high+low)/2;
  build(ind*2 + 1 , low , mid,v);
  build(ind*2 + 2 , mid+1 , high ,v);
  segment[ind] = min(segment[ind*2+1] , segment[ind*2+2]);
 }
 //Query
 int query(int ind, int low, int high , int target_low , int target_high, vector<int> &v){
  if(low >  target_high || high < target_low) return INT_MAX;
  if(low>=target_low && high<=target_high) return segment[ind];
  int mid = (low+high)/2;
  int ans1 = query(ind*2+1,low,mid,target_low,target_high,v);
  int ans2 = query(ind*2+2,mid+1,high,target_low,target_high,v);
  return min(ans1,ans2);
 }
 // Update Value
 void update(int ind , int low, int high , int target_ind , int val , vector<int>&v){
  if(low == high){
   segment[ind] = val;
   return;
  }
  int mid = (low+high)/2;
  if(target_ind<=mid) update(ind*2 + 1 , low , mid , target_ind , val , v);
  else update(ind*2 + 2 , mid+1 , high, target_ind, val  , v);
  segment[ind] = min(segment[ind*2+1] , segment[ind*2+2]);
 }
};
int main()
{
 int n; cin >> n;
 vector<int>v(n);
 for(auto &x : v) cin >> x;
 SegmentTree sg(n);
 sg.build(0,0,n-1,v);
 for(int i=0;i<4*n;i++){
  cout << sg.segment[i] << " ";
 }
 cout << endl;
 int q; cin >> q;
 while(q--){
  int type ; cin >> type;
  if(type==1){
   int l,r; cin >> l >> r;
   cout << sg.query(0,0,n-1,l,r,v) << endl;
  }
  else{
   int ind,val; cin >> ind >> val;
   sg.update(0,0,n-1,ind,val,v);
  }
 }
cout << endl;
