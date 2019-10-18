# Locale thingy
export LC_ALL=en_US.UTF-8

# Default editor
export EDITOR=/usr/bin/nano

# Git bash completion
[[ -r "/usr/local/etc/profile.d/bash_completion.sh" ]] && . "/usr/local/etc/profile.d/bash_completion.sh"

# Git branch name in terminal
parse_git_branch() {
  git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}

# Terminal prompt
export PS1="\[\e]0;\W\a\]\u@\h \[\033[36m\]\W\[\033[32m\]\$(parse_git_branch)\[\033[00m\] $ "

# Aliases
alias activate='source ./venv/bin/activate'
alias python2='python'

# Init pyenv
eval "$(pyenv init -)"
