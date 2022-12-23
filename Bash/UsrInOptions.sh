#!/bin/bash

# proof of concept for user inputs
# Prompt the user for input
echo "Say Hello or Bye"
echo "Enter a message: "
read message

# Check the value of the message and output the appropriate response
if [ "$message" == "Hello" ]; then
  echo "Go away"
  echo "Hello"
elif [ "$message" == "Bye" ]; then
  echo "Come back"
  echo "bye"
else
  echo "I don't understand your message"
fi

