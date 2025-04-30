
### stripe cli

- [install on linux](https://docs.stripe.com/stripe-cli?install-method=linux)

```bash
stripe login --interactive
# paste your stripe_secret_key
```

- stripe CLI stores credentials at `~/.config/stripe/config.toml` on Linux

### [stripe integration testing](https://docs.stripe.com/testing#cards)

```text
email:
xyz@gmail.com

card number:
4242424242424242

cvc:
333

future date:
04/30

# following is the dummy address generated from chatGPT
Cardholder name:
Jessica Miller

Billing address:
Country: 
United States

Address line 1: 
456 Elm Street

Address line 2: 
Suite 12

City: 
San Francisco

PIN (ZIP): 
94107

State: 
California
```

