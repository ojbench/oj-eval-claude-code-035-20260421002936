#!/usr/bin/env python3
import os
import json
from submit_acmoj.acmoj_client import ACMOJClient

# Get tokens from environment
acmoj_token = os.environ.get("ACMOJ_TOKEN")
problem_id = 2493

# Create client
client = ACMOJClient(acmoj_token)

# Submit via git
git_url = "https://github.com/ojbench/oj-eval-claude-code-035-20260421002936.git"
result = client.submit_git(problem_id, git_url)

if result:
    print(json.dumps(result, indent=2))
else:
    print("Submission failed")
