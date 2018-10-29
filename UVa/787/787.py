while True:
    a=[]
    t=1
    while True:
        try:
            s=input()
        except EOFError:
            break
        for i in s.split():
            t=int(i)
            if t==-999999:
                break
            a.append(t)
        if t==-999999:
            break
        print(t)

    if len(a)==0:
        break
    ans=a[0]
    dp=[[1]*len(a)]*len(a)
    for i in range(0,len(a)):
        for j in range(i,len(a)):
            if j>i:
                dp[i][j]=a[j]*dp[i][j-1]
            else:
                dp[i][j]=a[i]
            if dp[i][j]>ans:
                ans=dp[i][j]
    print(ans)


