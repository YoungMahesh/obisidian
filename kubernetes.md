```bash
microk8s kubectl version
kubectl run my-nginx --image nginx
kubectl create deployment my-nginx --image nginx
kubectl get all
kubectl get pods
kubectl delete pod my-nginx
kubectl describe deployment/my-nginx
kubectl delete deployment my-nginx

# installation
sudo snap install microk8s --classic
```

### pods
- smallest and simplest unit in the Kubernetes object model
- represents a single instance of a running process in a cluster and can contain on or more containers
- containers within a pod share the same network namespace, allowing them to communicate with each other using localhost and  storage volumes

### replicas
- refere to the number of identical copies of a pod that are running concurrently
- replication is a key concept in ensuring the availability, scalibility, and reliability of applications deployed in a Kubernetes cluster
- ReplicaSet
  - primary kubernetes resource used for managing replicas 
  - ensures that a specified number of replicas for a pod are running at all times
  - if the actual number of replicas deviates from the desired state, the ReplicaSet takes corrective action to bring the actual state in line with the desired state 