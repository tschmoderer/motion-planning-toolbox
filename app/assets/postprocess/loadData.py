#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import re
import json
import numpy as np

def remove_comments(string):
    pattern = r"(\".*?\"|\'.*?\')|(/\*.*?\*/|//[^\r\n]*$)"
    # first group captures quoted strings (double or single)
    # second group captures comments (//single-line or /* multi-line */)
    regex = re.compile(pattern, re.MULTILINE|re.DOTALL)
    def _replacer(match):
        # if the 2nd group (capturing comments) is not None,
        # it means we have captured a non-quoted (real) comment string.
        if match.group(2) is not None:
            return "" # so we will return empty to remove the comment
        else: # otherwise, we will return the 1st group
            return match.group(1) # captured quoted-string
    return regex.sub(_replacer, string)

def remove_not_run_exp(data): 
    data["experiences"] = [x for x in data["experiences"] if x["run"]]
    return data

def load_json_data(fname):
    with open(fname, 'r') as jsonfile:
        jsondata = ''.join(line for line in jsonfile)
        data = json.loads(remove_comments(jsondata))
        data = remove_not_run_exp(data)
    
    print("-- " + str(len(data["experiences"])) + " experience(s) will be processed\n")
    return data

def load_np_data(dir, data):
    res = []
    nbX0 = len(data["trajectories"]["x0"])
    fdir = data["outputs"]["structure"]["dir"]
    subfdir = data["outputs"]["trajectories"]["file"]["subdir"]
    fname = data["outputs"]["trajectories"]["file"]["filename"]
    tsfname = data["outputs"]["trajectories"]["file"]["time-filename"]
    for i in range(nbX0):
        tmp = fname.split('.')
        new_fname = dir + "/" + fdir + data["name"] + "/" + subfdir + tmp[0] + '-' + str(i+1) + '.' + tmp[1]
        tmp = tsfname.split('.')
        new_tsfname = dir + "/" + fdir + data["name"] + "/" + subfdir + tmp[0] + '-trajectory' + '-' + str(i+1) + '.' + tmp[1]
        time = np.loadtxt(new_tsfname, dtype='d', delimiter=',')
        traj = np.loadtxt(new_fname, dtype='d', delimiter=',')

        res.append(np.column_stack((time,traj)))

    return res
    