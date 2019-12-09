# Gradle boilerplate code snippets

## Setting up Gradle

For the original information, please visit [https://guides.gradle.org/building-java-applications/](https://guides.gradle.org/building-java-applications/)

Initializing a Java application project: `gradle init --type java-application`
For a Java library: `gradle init --type java-library`

In file `settings.gradle`, check "rootProject.name = 'something'"
In file `build.gradle`, check "mainClassName = ''"


## Build.gradle

This is what I consider a typical build.gradle configuration to use in my projects.

Several things about this:

- It has a Processing core library for graphics
- It has a JSON library
- It has a plugin for creating a deployable .jar file
- One of the dependency location is the /libs folder

```
buildscript {
    repositories {jcenter()}
    dependencies {classpath 'com.github.jengelman.gradle.plugins:shadow:4.0.2'}
}

plugins {
    id 'java'
    id 'application'
    id 'com.github.johnrengelman.shadow' version '4.0.2'
}

mainClassName = 'some.package.SomeMainClass'

dependencies {
    implementation 'com.google.guava:guava:23.0'
    implementation 'org.processing:core:3.3.7'
    implementation 'org.json:json:20140107'
    implementation fileTree("libs")

    testImplementation 'junit:junit:4.12'
    testImplementation 'org.json:json:20140107'
}

repositories {
    jcenter()
    mavenCentral()
    maven { url 'https://jitpack.io' } // this is for custom libraries that you can upload to Jitpack for free
}

jar {manifest {attributes 'Main-Class': mainClassName}}
```

If you happen to want to change the JDK version, add this:

```
compileJava.options.fork = true
compileJava.options.forkOptions.executable = "path/to/javac"
```
