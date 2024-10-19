#!/bin/bash

# Navigate to the root of the repository (assumes script is inside the `website` folder)
cd ../../..

# Check if on the main branch
CURRENT_BRANCH=$(git branch --show-current)
if [ "$CURRENT_BRANCH" != "main" ]; then
    echo "You must be on the 'main' branch to deploy."
    exit 1
fi

# Push the website directory to gh-pages
git subtree push --prefix documents/documentation/website origin pages

# Optional: Return success message
if [ $? -eq 0 ]; then
    echo "Deployment successful!"
else
    echo "Deployment failed!"
fi
