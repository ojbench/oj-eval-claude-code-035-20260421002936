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

# Read the git URL
git_url = "https://github.com/ojbench/oj-eval-claude-code-035-20260421002936.git"

# Submit via git
data = {"language": "git", "code": git_url}
url = f"{api_base}/problem/{problem_id}/submit"

try:
    response = requests.post(url, headers=headers, data=data, timeout=10, proxies={"https": None, "http": None})
    print(f"Status Code: {response.status_code}")
    print(f"Response: {response.text}")
    response.raise_for_status()
    result = response.json()
    print(json.dumps(result, indent=2))
except Exception as e:
    print(f"Error: {e}")
