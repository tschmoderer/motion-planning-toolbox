import json 
import logging

import re

logger = logging.getLogger("main")

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

def data_has(data, key): 
    if not key in data: 
        raise Exception("Experience should have a key : " + key + ".")

def data_is_in(value, list, key): 
    if not value in list: 
        raise Exception("Error for key : " + str(key) + "should be in list : " + str(list))

    
exp_types = ["dynamical", "control"]

def check_single_exp(data): 
    data_has(data, "type")
    data_is_in(data["type"], exp_types, "type")

    data_has(data, "name")

    data_has(data, "dimensions")
    data_has(data["dimensions"], "state_dim")
    if data["type"] == "control": 
        data_has(data["dimensions"], "ctrl_dim")

    data_has(data, "times")
    data_has(data["times"], "start")
    data_has(data["times"], "end")

    data_has(data, "dynamics")
    data_has(data["dynamics"], "f")

def check(data): 
    data_has(data, "experiences")
    k = 0

    for d in data["experiences"]: 
        data_has(d, "run")
        if d["run"]:
            k = k + 1
            logger.info("Check json configuration for exp # " + str(k)) 
            check_single_exp(d)


def load_json_data(fname):
    logger.debug("Open configuration file")
    with open(fname, 'r') as jsonfile:
        jsondata = ''.join(line for line in jsonfile)
   
    logger.debug("Load confguration file as .json.")
    data = json.loads(remove_comments(jsondata))

    logger.debug("Configuration data will be checked.")
    check(data)

    logger.debug("We remove not runned experiment(s).")
    data = remove_not_run_exp(data)
    
    logger.info(str(len(data["experiences"])) + " experience(s) will be performed.")

    return data