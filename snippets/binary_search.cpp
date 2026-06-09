int low=0, high=1e18, ans=-1;
while(low<=high)
{
    int mid = low + (high-low)/2;
    if(v[mid]==target)
    {
        ans = mid;
        break;
    }
    else if(v[mid]<target) low = mid+1;
    else high = mid-1;
}
cout<<ans<<endl;
