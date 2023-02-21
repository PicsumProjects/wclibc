output= 
update_ver() {
    build=$1
    minor=$2
    major=$3
    
    if [[ "$build" == "9" ]]; then
        carry_build=true
        build=0
    fi
    
    if [[ "$carry_build" == "true" ]] && [[ "$minor" == "9" ]]; then
        carry_minor=true
        minor="0"
    elif [[ "$carry_build" == "true" ]]; then
        (( minor = minor + 1 ));
    fi
    
    if [[ "$carry_minor" == "true" ]]; then
        (( major = major + 1 ))
    fi
    
    output=${major}.${minor}.${build}
}

IFS=.
read -r major minor build <<< $(cat version)
update_ver $build $minor $major
echo $output > ./version
