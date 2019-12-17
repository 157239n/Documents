
This is for the kind software, or Kubernetes IN Docker. It's supposed to act like minikube, but with less overhead. This is sort of a scaled down version of k8s, which runs on a single node only

# Installation:
- kind: curl -Lo ./kind https://github.com/kubernetes-sigs/kind/releases/download/v0.6.1/kind-$(uname)-amd64
- kubectl: curl -LO https://storage.googleapis.com/kubernetes-release/release/`curl -s https://storage.googleapis.com/kubernetes-release/release/stable.txt`/bin/linux/amd64/kubectl

kind project, "kubernetes in docker", https://kind.sigs.k8s.io/
export KUBECONFIG="$(kind get kubeconfig-path)"
kind delete cluster

# Kind commands

## Creating a cluster
### kind create cluster --name {cluster name=kind}
```
root@ubuntu-2:~/test/kind# kind create cluster
Creating cluster "kind" ...
 ✓ Ensuring node image (kindest/node:v1.16.3) 🖼 
 ✓ Preparing nodes 📦 
 ✓ Writing configuration 📜 
 ✓ Starting control-plane 🕹️ 
 ✓ Installing CNI 🔌 
 ✓ Installing StorageClass 💾 
Set kubectl context to "kind-kind"
You can now use your cluster with:

kubectl cluster-info --context kind-kind

Have a nice day! 👋
```

## Diagnostics
### kind get clusters
```
root@ubuntu-2:~/test/kind# kind get clusters
kind
```
## Deleting a cluster
```
root@ubuntu-2:~/test/kind# kind delete cluster --name kind
Deleting cluster "kind" ...

root@ubuntu-2:~/test/kind# kubectl version
Client Version: version.Info{Major:"1", Minor:"17", GitVersion:"v1.17.0", GitCommit:"70132b0f130acc0bed193d9ba59dd186f0e634cf", GitTreeState:"clean", BuildDate:"2019-12-07T21:20:10Z", GoVersion:"go1.13.4", Compiler:"gc", Platform:"linux/amd64"}
The connection to the server localhost:8080 was refused - did you specify the right host or port?
```

kind load docker-image my-custom-image --name kind-{cluster name}, workflow allowed:
docker build -t my-custom-image:unique-tag ./my-image-dir
kind load docker-image my-custom-image:unique-tag
kubectl apply -f my-manifest-using-my-image:unique-tag

# K8S commands
## Diagnostics
### kubectl cluster-info [--context kind-{cluster name}]
```
root@ubuntu-2:~/test/kind# kubectl cluster-info --context kind-kind
Kubernetes master is running at https://127.0.0.1:44481
KubeDNS is running at https://127.0.0.1:44481/api/v1/namespaces/kube-system/services/kube-dns:dns/proxy

To further debug and diagnose cluster problems, use 'kubectl cluster-info dump'.
```
### kubectl version
```
root@ubuntu-2:~/test/kind# kubectl version
Client Version: version.Info{Major:"1", Minor:"17", GitVersion:"v1.17.0", GitCommit:"70132b0f130acc0bed193d9ba59dd186f0e634cf", GitTreeState:"clean", BuildDate:"2019-12-07T21:20:10Z", GoVersion:"go1.13.4", Compiler:"gc", Platform:"linux/amd64"}
Server Version: version.Info{Major:"1", Minor:"16", GitVersion:"v1.16.3", GitCommit:"b3cbbae08ec52a7fc73d334838e18d17e8512749", GitTreeState:"clean", BuildDate:"2019-12-04T07:23:47Z", GoVersion:"go1.12.12", Compiler:"gc", Platform:"linux/amd64"}
```
### kubectl get componentstatuses
```
root@ubuntu-2:~/test/kind# kubectl get componentstatuses
NAME                 AGE
controller-manager   <unknown>
scheduler            <unknown>
etcd-0               <unknown>
```
### kubectl get nodes
```
root@ubuntu-2:~/test/kind# kubectl get nodes
NAME                 STATUS   ROLES    AGE   VERSION
clu1-control-plane   Ready    master   21m   v1.16.3
```
### kubectl describe {resource type, nodes} {resource name, node name right above}
```
root@ubuntu-2:~# kubectl describe node clu1
Name:               clu1-control-plane
Roles:              master
Labels:             beta.kubernetes.io/arch=amd64
                    beta.kubernetes.io/os=linux
                    kubernetes.io/arch=amd64
                    kubernetes.io/hostname=clu1-control-plane
                    kubernetes.io/os=linux
                    node-role.kubernetes.io/master=
Annotations:        kubeadm.alpha.kubernetes.io/cri-socket: /run/containerd/containerd.sock
                    node.alpha.kubernetes.io/ttl: 0
                    volumes.kubernetes.io/controller-managed-attach-detach: true
CreationTimestamp:  Mon, 16 Dec 2019 18:18:50 +0000
Taints:             <none>
Unschedulable:      false
Lease:
  HolderIdentity:  clu1-control-plane
  AcquireTime:     <unset>
  RenewTime:       Mon, 16 Dec 2019 18:42:27 +0000
Conditions:
  Type             Status  LastHeartbeatTime                 LastTransitionTime                Reason                       Message
  ----             ------  -----------------                 ------------------                ------                       -------
  MemoryPressure   False   Mon, 16 Dec 2019 18:41:50 +0000   Mon, 16 Dec 2019 18:18:46 +0000   KubeletHasSufficientMemory   kubelet has sufficient memory available
  DiskPressure     False   Mon, 16 Dec 2019 18:41:50 +0000   Mon, 16 Dec 2019 18:18:46 +0000   KubeletHasNoDiskPressure     kubelet has no disk pressure
  PIDPressure      False   Mon, 16 Dec 2019 18:41:50 +0000   Mon, 16 Dec 2019 18:18:46 +0000   KubeletHasSufficientPID      kubelet has sufficient PID available
  Ready            True    Mon, 16 Dec 2019 18:41:50 +0000   Mon, 16 Dec 2019 18:19:50 +0000   KubeletReady                 kubelet is posting ready status
Addresses:
  InternalIP:  172.17.0.2
  Hostname:    clu1-control-plane
Capacity:
  cpu:                2
  ephemeral-storage:  25226960Ki
  hugepages-1Gi:      0
  hugepages-2Mi:      0
  memory:             4039608Ki
  pods:               110
Allocatable:
  cpu:                2
  ephemeral-storage:  25226960Ki
  hugepages-1Gi:      0
  hugepages-2Mi:      0
  memory:             4039608Ki
  pods:               110
System Info:
  Machine ID:                 dd7e869ae51e4c24bc395ae3427cda3d
  System UUID:                64e5b4d8-58c0-4df9-9f95-678dcae8a13d
  Boot ID:                    251d264e-dc1b-49fc-ae06-e709fa802981
  Kernel Version:             4.15.0-72-generic
  OS Image:                   Ubuntu Eoan Ermine (development branch)
  Operating System:           linux
  Architecture:               amd64
  Container Runtime Version:  containerd://1.3.0-27-g54658b88
  Kubelet Version:            v1.16.3
  Kube-Proxy Version:         v1.16.3
PodCIDR:                      10.244.0.0/24
PodCIDRs:                     10.244.0.0/24
Non-terminated Pods:          (8 in total)
  Namespace                   Name                                          CPU Requests  CPU Limits  Memory Requests  Memory Limits  AGE
  ---------                   ----                                          ------------  ----------  ---------------  -------------  ---
  kube-system                 coredns-5644d7b6d9-btrd9                      100m (5%)     0 (0%)      70Mi (1%)        170Mi (4%)     23m
  kube-system                 coredns-5644d7b6d9-k8mzs                      100m (5%)     0 (0%)      70Mi (1%)        170Mi (4%)     23m
  kube-system                 etcd-clu1-control-plane                       0 (0%)        0 (0%)      0 (0%)           0 (0%)         22m
  kube-system                 kindnet-jkrn2                                 100m (5%)     100m (5%)   50Mi (1%)        50Mi (1%)      23m
  kube-system                 kube-apiserver-clu1-control-plane             250m (12%)    0 (0%)      0 (0%)           0 (0%)         22m
  kube-system                 kube-controller-manager-clu1-control-plane    200m (10%)    0 (0%)      0 (0%)           0 (0%)         22m
  kube-system                 kube-proxy-6mjbw                              0 (0%)        0 (0%)      0 (0%)           0 (0%)         23m
  kube-system                 kube-scheduler-clu1-control-plane             100m (5%)     0 (0%)      0 (0%)           0 (0%)         22m
Allocated resources:
  (Total limits may be over 100 percent, i.e., overcommitted.)
  Resource           Requests    Limits
  --------           --------    ------
  cpu                850m (42%)  100m (5%)
  memory             190Mi (4%)  390Mi (9%)
  ephemeral-storage  0 (0%)      0 (0%)
Events:
  Type     Reason                   Age                From                            Message
  ----     ------                   ----               ----                            -------
  Normal   NodeHasSufficientMemory  23m (x8 over 23m)  kubelet, clu1-control-plane     Node clu1-control-plane status is now: NodeHasSufficientMemory
  Normal   NodeHasNoDiskPressure    23m (x7 over 23m)  kubelet, clu1-control-plane     Node clu1-control-plane status is now: NodeHasNoDiskPressure
  Normal   NodeHasSufficientPID     23m (x8 over 23m)  kubelet, clu1-control-plane     Node clu1-control-plane status is now: NodeHasSufficientPID
  Warning  readOnlySysFS            23m                kube-proxy, clu1-control-plane  CRI error: /sys is read-only: cannot modify conntrack limits, problems may arise later (If running Docker, see docker issue #24000)
  Normal   Starting                 23m                kube-proxy, clu1-control-plane  Starting kube-proxy.
```
### kubectl get {resource type} --all-namespaces [--namespace={namespace}]
```
root@ubuntu-2:~# kubectl get deployments --all-namespaces
NAMESPACE     NAME      READY   UP-TO-DATE   AVAILABLE   AGE
kube-system   coredns   2/2     2            2           6m24s
```
```
root@ubuntu-2:~# kubectl get services --all-namespaces
NAMESPACE     NAME         TYPE        CLUSTER-IP   EXTERNAL-IP   PORT(S)                  AGE
default       kubernetes   ClusterIP   10.96.0.1    <none>        443/TCP                  6m42s
kube-system   kube-dns     ClusterIP   10.96.0.10   <none>        53/UDP,53/TCP,9153/TCP   6m40s
```
```
root@ubuntu-2:~# kubectl get pods --all-namespaces
NAMESPACE     NAME                                         READY   STATUS    RESTARTS   AGE
kube-system   coredns-5644d7b6d9-4qff2                     1/1     Running   0          8m11s
kube-system   coredns-5644d7b6d9-c5cjq                     1/1     Running   0          8m11s
kube-system   etcd-clu1-control-plane                      1/1     Running   0          7m11s
kube-system   kindnet-8rhhh                                1/1     Running   0          8m11s
kube-system   kube-apiserver-clu1-control-plane            1/1     Running   0          7m8s
kube-system   kube-controller-manager-clu1-control-plane   1/1     Running   0          7m9s
kube-system   kube-proxy-c4ld7                             1/1     Running   0          8m11s
kube-system   kube-scheduler-clu1-control-plane            1/1     Running   0          7m25s
```
### kubectl config set-context context1 --namespace=namespace1
```
root@ubuntu-2:~/.kube# kubectl config set-context context1 --namespace=namespace1
Context "context1" created.
```
### kubectl config use-context context1
```
root@ubuntu-2:~/.kube# kubectl config use-context context1
Switched to context "context1".
```
### kubectl apply -f obj.yaml \[--dry-run\] \[edit-last-applied | set-last-applied | view-last-applied\]
### kubectl delete -f obj.yaml \[--dry-run\]
### kubectl edit {resource type} {resource name}
### kubectl delete {resource type} {resource name}
### kubectl label pods bar color=red
### kubectl label pods bar color-
### kubectl logs {pod name}
### kubectl exec {pod name} date
### kubectl exec -it {pod name} -- bash
### kubectl attach -it {pod name}
### kubectl cp {pod name}:{path to remote file} {path to local file}
### kubectl port-forward {pod name | 'services' | service name} 8080:80
Opens a connection that forwards traffic from local machine on 8080 to remote container's port 80. Can forward to a service inside of a pod, but not to the service's load balancer and gets distributed to all pods
### kubectl top nodes
### kubectl top pods
### kubectl help {command name}

## Pods
### Yml file
optionals:
- livenessProbe
```
apiVersion: v1
kind: Pod
metadata:
  name: kuard
spec:
  containers:
    - image: gcr.io/kuar-demo/kuard-amd64:blue
      name: kuard
      ports:
        - containerPort: 8080
          name: http
          protocol: TCP
      livenessProbe:
        httpGet:
          path: /healthy
          port: 8080
        initialDelaySeconds: 5
        timeoutSeconds: 1
        periodSeconds: 10
        failureThreshold: 3
```

### kubectl port-forward --address 0.0.0.0 kuard 8080:8080 2>/dev/null 1>&2 &
### kubectl exec kuard date
Also, -it and sh is available, kinda similar to docker heh?




