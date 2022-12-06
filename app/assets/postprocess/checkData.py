#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def data_has(data, key): 
    if not key in data: 
        raise Exception("Experience should have a key : " + key + ".")

def check_experiment(data): 
    data_has(data, "outputs")
    data_has(data["outputs"], "structure")
    data_has(data["outputs"]["structure"], "dir")
    data_has(data["outputs"], "trajectories")
    data_has(data["outputs"]["trajectories"], "file")
    data_has(data["outputs"]["trajectories"]["file"], "yn")

    if not data["outputs"]["trajectories"]["file"]["yn"]: 
        raise Exception("Error: you should provide output files for yur experiment.")

    data_has(data, "postprocess")
    data_has(data["postprocess"], "plots")
    for i in range(len(data["postprocess"]["plots"])):
        data_has(data["postprocess"]["plots"][i], "what")
        data_has(data["postprocess"]["plots"][i], "data")
        data_has(data["postprocess"]["plots"][i]["data"], "x")
        data_has(data["postprocess"]["plots"][i]["data"], "y")
        data_has(data["postprocess"]["plots"][i]["data"], "nb")


def check_data(data): 
    for k in range(len(data["experiences"])):
        check_experiment(data["experiences"][k])
