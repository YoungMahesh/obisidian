### Configure domain provider

1. Visit your domain-provider (e.g. `domains.google.com`)
1. Go to `DNS` -> `Default name servers` -> `Custom records` -> `Manage custom records`
1. point domain to your ip address
   - Host name: name of subdomain, e.g. `whoami` for `whoami.example.com`, keep empty if you are going to use main domain like `example.com`
   - Type: `A`
   - Data or Target: ip-address of your server/vps, e.g. `76.76.21.21`
   - Keep value of `TTL` as it is
1. point all subdomains to your ip address
   - Host name: \*
   - Type: A
   - Data or Target: ip-address of your server/vps, e.g. `76.76.21.21`

