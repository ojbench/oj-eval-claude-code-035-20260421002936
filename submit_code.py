#!/usr/bin/env python3
import os
import json
import requests

# Get tokens from environment
acmoj_token = os.environ.get("ACMOJ_TOKEN")
problem_id = 2493

api_base = "https://acm.sjtu.edu.cn/OnlineJudge/api/v1"
headers = {
    "Authorization": f"Bearer {acmoj_token}",
    "Content-Type": "application/x-www-form-urlencoded",
    "User-Agent": "ACMOJ-Python-Client/2.2"
}

# Read the code file
with open("MyString.hpp", "r") as f:
    code = f.read()

# Submit as C++ code
data = {"language": "cpp", "code": code}
url = f"{api_base}/problem/{problem_id}/submit"

try:
    response = requests.post(url, headers=headers, data=data, timeout=10, proxies={"https": None, "http": None})
    print(f"Status Code: {response.status_code}")
    print(f"Response: {response.text}")
    if response.status_code in [200, 201]:
        result = response.json()
        print("\nSubmission successful!")
        print(json.dumps(result, indent=2))
        if 'id' in result:
            print(f"\nSubmission ID: {result['id']}")
            print(f"Remember this ID for checking status!")
except Exception as e:
    print(f"Error: {e}")
