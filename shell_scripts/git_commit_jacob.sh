git config --global user.name "jacobollinger"
git config --global user.email "7657565+jacobollinger@users.noreply.github.com"

read -p "Please enter the commit message: " commit_message

git commit -m "$commit_message"

git config --unset --global user.name
git config --unset --global user.email