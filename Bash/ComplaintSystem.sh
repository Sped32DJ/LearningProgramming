#!/bin/bash

echo "Enter Name:"
read name
echo "Hello, $name"

echo "Do you have a complaint?"
read complaint
echo $complaint > /dev/null
echo
sleep 1
echo "We are analyzing your complaint..."
sleep 1
echo "..."
sleep 1
echo
echo "Well, that complaint has been sent to our systems > /dev/null"
