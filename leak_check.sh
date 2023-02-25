#!/bin/bash
pid=$(pgrep minishell)
while true; do leaks -nostacks $pid; sleep 2; done;
