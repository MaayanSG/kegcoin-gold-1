import requests
import ujson as json
import sys
import binascii

to_address = "KbCPp53czX4dRAp9Jg73cyHN5tW6pDgDcJey5VQxK7aH7aMAC7JbosF4sruY7nRBhD9P5zJbqYnbi9hnY6zwuLj2Vp31S68"
content = """
  _
 | | /\
 | |/ /
 | | /
 | |\ \
 |_|\__\
"""

def rpc(method, params={}):
    base_url = "http://localhost:5000/json_rpc"
    payload = {
        "password": "80085",
        "jsonrpc" : "2.0",
        "method" : method,
        "params" : params,
        "id" : "blah"
    }

    try:
        response = requests.post(base_url, data=json.dumps(payload)).json()
    except Exception as e:
        print("Doesn't seem like kegcoin-service is running. {}".format(response))
        sys.exit(1)

    if 'error' in response:
        print("Failed to talk to server. {}".format(response))
        sys.exit(1)
    return response

r = rpc("sendTransaction", {
    "transfers": [{
        "amount": 1,
        "address": to_address,
    }],
    "fee": 10,
    "anonymity": 1,
    "extra": binascii.hexlify(content.encode()).decode()
})
print(r)
