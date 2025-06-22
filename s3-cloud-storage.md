# minio implementation

### 1. start minio container

  ```yml
  services:
    minio:
      image: minio/minio:RELEASE.2025-02-07T23-21-09Z
      container_name: minio
      ports:
        # S3_endpoint for host: http://localhost:9000/
        # S3_endpoint for other docker containers: http://minio:9000/
        #   here in this url 'minio' is container_name
        - "9000:9000"
        # s3 ui dashboard
        - "9001:9001"
      volumes:
        # directory $HOME/minio/data will be mounted in container at /data, this will store all files uploaded to minio
        - ~/minio/data:/data
      environment:
        # credentials to login through ui at localhost:9001/
        - MINIO_ROOT_USER=ROOTNAME
        - MINIO_ROOT_PASSWORD=CHANGEME123
        
        
        # create bucket through ui: http://localhost:9001/
      command: server /data --console-address ":9001"  
  ```
### 2. setup environment

- create (access_key + secret_key) combination through ui: User -> Access Keys

- add related variables in .env file

  ```.env
  S3_ENDPOINT=http://localhost:9000
  S3_ACCESS_KEY=<generated-access-key/username>
  S3_SECRET_KEY=<generated-secret-key/password>
  S3_BUCKET_NAME="my-bucket"
  ```

### relationship between rootUser, user, accessKeys

- user (normal user or rootUser) can create accessKeys
- accessKeys only have programaticAccess
- user credentials can be used as accessKey(username) and secretKey(password)
- user credentials can be used for console-access(login to ui), api-access and programmaticAccess 

```mermaid
classDiagram
    RootUser --|> User
    User --|> AccessKeys
    class RootUser {
        +createPolicies()
        +assignPoliciesToUser()
        +consoleAccess
        +APIAccess
        +programmaticAccess
        +createUsers()
        +createAccessKeys()
    }
    class User {
        +inheritPoliciesFromParent()
        +assignPoliciesToAccessKeys()
        +consoleAccess
        +APIAccess
        +programmaticAccess
        +createAccessKeys()
    }
    class AccessKeys {
        +inheritPoliciesFromParent()
        +programmaticAccess
    }
```

### cli usage
- create bucket
  - download and install [minio command line - mc](https://dl.min.io/client/mc/release/linux-amd64/)

  ```bash
  # set connection
  # mc alias set <custom-connection-name> <endpoint> <username> <password> 
  #    username and password here are set in docker-compose file above
  # this connection will be stored in ~/.mc/config.json
  mc alias set minio-admin http://localhost:9000 ROOTNAME CHANGEME123
  mc alias ls
  mc admin info minio-admin

  mc admin user add minio-admin user1 password1
  mc admin user ls minio-admin

  # give privalages to user
  # list policies
  mc admin policy list minio-admin
  # read specific policy
  mc admin policy info minio-admin readonly
  # attach policy to user; here are giving readwrite access to user1 for 'all buckets'
  mc admin policy attach minio-admin readwrite --user user1
  mc admin policy entities minio-admin --user user1
  # create user connection
  mc alias set conn1 http://localhost:9000 user1 password1
  # this will fail, as we given user readwrite access but not administrative access; this way we have created limited access user
  # now we can use this user-credentials as: S3_ACCESS_KEY, S3_SECRET_KEY
  mc admin info conn1 

  # create bucket
  # mc mb(make-bucket) <connection-name>/<bucket-name>
  mc mb conn1/bucket1
  # list buckets
  mc ls conn1
  # copy file to bucket
  mc cp ./file1.txt conn1/bucket1
  mc ls conn1/bucket1
  # put file in a folder
  # this folder structure is only better user-experience, in reality all files are in bucket-root with path-name as their identifier
  mc cp ./file2.txt conn1/bucket1/folder1
  # move file between buckets
  mc mv conn1/bucket1/file1.txt conn1/bucket2 
  ```


# [s3](simple storage server) object storage

- store and manage data as objects rather than as files or blocks
- each object is self contained and includes metadata that describes the object's content and attributes
- objects can accessed directly through a unique identifier rather than through a file system hierarchy, which can improve performance

- data security

  - securing access to data: applying permissions, object and bucket settings, access control, policy conditions
  - protecting data: encrypting data, data recovery, replication, versioning

- access
  - resource-based security: bucket policies, object ACLs, bucket ACLs, bucket ownership
  - user-based security: IAM policies

## buckets

- on s3 storage we store each file in a bucket, each bucket will have globally unique name; once created, you cannot change the bucket name
- objects and buckets can be made public
- we can either make whole bucket public or private, s3 doesn't support block public access settings on a per-object basis
- since january 2023, AWS made SSE-S3 the default encryption method for all new object uploads to Amazon S3.
  This change means that any new data uploaded is automatically encrypted without any additional cost or performance impact,
  further enhancing security measures

### access keys + bucket policy

- Access Keys
  - Attached to IAM users, groups, or roles; Controls what a user can do in AWS
  - Do not directly control access to individual objects; IAM policies typically apply broadly based on the user's role or group
  - long-term credentials for an IAM user or the AWS account root user, used to sign programmatic requests
    to the AWS CLI or AWS API. They consist of an access key ID and a secret access key.
- Bucket policies
  - Attached to an S3 bucket; Controls who can access a bucket
  - Can specify permissions at the object level by including the object as the resource in the bucket policy
  - are resource-based policies that you attach to an S3 bucket to grant access permissions to the bucket
    and the objects within it. They are written in JSON, using the AWS Identity and Access Management (IAM) policy language.
    Only the bucket owner can associate a policy with a bucket
- Fundamentally, access keys are about who is making the request, while bucket policies are about what they can do with the bucket
  and its contents. They often work together to provide a comprehensive security model for AWS resources.

---

# optional

## access control lists (ACLs)

- for new buckets, ACLs are disabled by default
- AWS recommends disabling ACLs to simplify permissions management and using policies to control access to all objects in your bucket,
  irrespective of who uploaded them
- ACLs allow you to set granular permissions for different AWS accounts or groups, granting or revoking access at the object level
