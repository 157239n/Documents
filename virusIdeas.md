
Note that all of these ideas below assume that the virus does not have admin rights. Not having admin rights kinda limits a lot of stuff that I can do, but there are still a bunch of stuff that I can do. For admin stuff, I sort of have to really buy a new zero day, or utilize a very, very recent one for it to be able to work. Zero days just cost too damn much, like in the 300k range or so

# Urgent

Sanitize getFile.php command, make sure directory traversal is impossible

# Big ideas

## Formulate session attacks

This should be a session attack. This means that when the virus receives the payload, it monitors the computer over a period of time, could range from 2 minutes to 30 minutes as a reasonable use. This can also be defined in cycles, if minutes are too much of a hassle. Then it just keeps reporting the result back in real time. This would be great for stuff like task monitoring and health checks, or screen monitoring.

Also this means that the admin page should automatically update in real time (which seems to incur another web server entry point), or it should automatically refresh in real time (which is less ideal because it can bother the heck out of users).

## Task monitoring

Proposed package: adv.session.MonitorTask

tasklist: image name (smss.exe, svchost.exe), pid (0, 4, 1372), session name (services, console), session (0, 1)
tasklist /v: image name, pid, mem usage, status unknown, user name, cpu time, window title
tasklist /fo csv
taskkill {/pid 9214 | /im image name | /fi ???}
for interpreting csv files sent back: https://www.php.net/manual/en/function.str-getcsv.php

## Key logging

Proposed package: easy.session.KeyLogging

May be try the C# path, learn about C# quickly, cause it has the distinct advantage of being able to compile right on the spot and windows won't flag it for its foreigness

https://github.com/kristian/system-hook. In the end, you will still have to use the windows api and thus, go on the native level anyway, so there is no escaping java native interface. Either this or do my shit in C#, but I hate microsoft, so no please

## Managing 3rd party binaries

The idea is that the virus can download pre-prepared binaries for doing a lot of stuff. It can install a java runtime binary, to run java programs. It can install embedded python, again, to run programs. But again, just installing it manually via the adv.ExecuteScrupt package is not sustainable and hard as fuck, so I sort of have to track it in the webserver, create a lib table, with name and virus_id for example. Examples of when this is useful:
- running a script in another language than batch? Sign me up
- controlling the volume

It's a good point to note that easy.Screenshot and unixtime.cmd can be considered a 3rd party library, but the main implementation is straightforward enough to not keep them in this managing 3rd party lib insanity. This idea is worth pursuing if there are much more attack packages in the future and they rely on complicated environments and whatnot, but for simple goals, it's not worth it.

Also note that this conflicts with the plans to auto migrate and cluster orchestration, because moving the entire virus is fucking heavy with 3rd party libs and dealing with dependencies might be so mind fucking.

Binaries I can think of right now:
- JRE (Joe Rogan lmao)
- python
- nircmd: http://www.nirsoft.net/utils/nircmd.html

## Session hijacking

Stealing cookies to use as my own. This is a bit dangerous, because I know that there will be other metrics facebook and google uses to fight against this, so I really have to get into the weeds of how these are implemented to be able to bypass them.

## Auto migrating, cluster management and orchestration

The idea is that on 1 host computer, all viruses know about the status of each other, like the number of viruses, what is their hash, etc. Then the webserver can issue a desired state of like, 5 viruses, with 1 manager node and 4 worker nodes. Then if the manager node disappears, then the worker nodes will try to bring it up. If one of the worker node disappears, the manager node will try to bring it up. The split between these is to just minimize race conditions if all viruses are created equal. If we really want to go into that equal route, then we have to study up on something like the raft consensus algorithm, which will be overkill.

They can share information using a common file that kinda act as a named pipe, or they can use a named pipe directly, but there might be restrictions to that, so using a file is still the best bet. If we really go on this path then may be make backups to the named pipe, like ditching it every 10 minutes or so. So they need to agree on some other central file long into the future to deal with unexpected named pipe shutdown by the antivirus.

And the auto migrating part, it's when a virus instance stop listening for new attacks, wait for every current attack to finish executing, then copies itself into another location where it has scouted before and deemed to be writable and safe. After that, it will fix the start up entry point to reflect the new location. This can happen every 30 minutes or something, and I think would evade the eyes of antivirus effectively.

For picking new host location, may be a list of candidate host locations from the webserver. But like, I can just do a recursive search, test permission, and if permission works, count up a counter, explore that directory and repeat, until the counter reached a random but pre-specified number, then that directory is selected. But like, that still is not random, assuming the first random generator is truely random. So, scans for permitted child directories, then pick a random directory among them and get into that. Then repeat again, for a random number of times from 0 to 8. That eliminates some deterministic behavior, but still sort of biased towards the earlier directories. But I guess this is sort of a price to pay. If I try to fix that with hierarchical-distributed randomness, that would kill the layer-distribution randomness, so pick one or another.

Also there is another way instead of copying locally, and that is to curl a special endpoint designed to do this, and starting up the new environment takes no brain power at all. But still, making an endpoint exposes another security risk to the webserver, and it will put more weight on it too, so is undesirable.

## Locking

The idea is that you can lock a directory, to prevent deletion by spawning processes that sort of listens to a directory forever.
So rough idea is to direct tree C:\ to a file you want to lock
- file exclusive lock (tl;dr: notepad >filetolock, and if writing, then is locked): https://stackoverflow.com/questions/25121516/how-to-get-an-exclusive-lock-on-a-file-using-batch-file

## Big file transferring

Transfer big files. I imagine if there is a tool to cut and assemble binaries without any corruption, then the payload can split up the file, then spawn processes to transfer each of the parts. Or can just send each part serially and having a delay in between, to prevent eating up all the host machine's bandwidth and by extension, prevent detection.

## Manipulating host computer's Certificate Authority

so, may be install a certificate authority on their machine, then reroute their hosts file, for dns spoofing, to collect basically every communication channels. But like, signing keys aren't an easy thing to do as of right now, because i don't fucking understand those .pem key files. Like, the signing process is a big deal.

Also, reroute their hosts file to what? Well, to my webserver, then that webserver will sort of be the middle man, and will establish a connection between it and the final website. I can technically do this right now on unencrypted connections. I can do this on encrypted connection as well, but there will be a bunch of red flags popping up. This might be a good strategy if hijacking the local certificate authority is not possible, and users will potentially click through the warnings anyway. The whole point of hijacking the local CA is to make it seems legit and to not raise any suspicion.

This can be seen as the ultimate attack, because if I can pull this off then every outbound and inbound connection can be listened to and be transmitted back to me, and the middle man is the webserver itself, so should be fast and cheap to just take everything.

But again, all of these is tricky to implement, because I'm pretty sure that adding an entry in the list of CAs is a big deal, and will be protected with the most stringent conditions.

## Dealing with stray viruses

figure out a rough estimate of the stray virus file size if i don't clear it ever so often. So, pings every ~10 seconds, returns back ~100 characters, each character takes 1 byte in utf-8. That would be 10 bytes per second. A month has 2.5mil seconds, which would mean 25MB of data, for one stray virus in a month. That's pretty wild. Shouldn't I direct the virus to log inside of the database? That would be more efficient, mass-wise. This would be neat, but not necessary.

an idea for attaching stray viruses to user accounts. When the account is active, the user can click a button, to get a config file A, and a random string B and the database stores hash(A, B). The B is the proof or ownership and you can't really guess the random string B if it's long. So, make it like that, make it long enough so that the security will not be breached. Then, the user can provide A and B, then the program reads A, checks if A is valid with the hash, then do the necessary association.

or, just go with the much simpler approach of sending the kill when an unknown virus pings. This is also interesting and may be I should have a self destruct script that can delete the virus-specific SU.vbs file, then I don't need to worry about micromanaging the local environment anymore and can just let the virus mutates freely. Also may be this is a way to have multiple viruses know where each of the viruses are and how many there are, because at the end of the day, there must still be an entrypoint anyway, right? You can't hide there

# Small ideas that can be implemented right away

## Adding attributes to easy.ExploreDir

Attributes that can be accessed using %%\~a
attrib +s +h autorun.inf
https://stackoverflow.com/questions/18658509/how-to-get-attributes-of-a-file-using-batch-file

## Securing startup entry point

The idea is to write over the virus's entry point at the startup folder every 10 minutes, so that even if some antivirus comes in and delete the file, it will still be created some time in the future and the virus will be secured against shutdowns.

## Kill signal

send kill signal and maintain that signal when deleting a virus. This would be more complicated to make it simple. The way I imagined to make it simple is to redirect that virus's ownership to myself, then add a new easy.SelfDestruct payload.

## Adding filters to easy.ExploreDir and Virus info page

## Using http instead of https for virus reporting

Well, on my machine, curl would sometimes access the webserver using https, but other times it doesn't. But http alone always work. But I kinda want to protect the target's data too, so I'm on the fence about this

## Publish to github

## Activates a link when virus is installed

For social engineering purposes

## Connect easy.ExploreDir and easy.CollectFile

how about on the explore dir, place a checkbox on the left and the user can check in the files they want to see, then click another button that will create a new attack automatically? I think this would be a precursor to me being able to integrate taskkill and tasklist

## Make a new, screenshot session attack

Proposed package: easy.session.ScreenshotSession

This should just report back screenshots repeatedly, for 15 minutes

## Modify entry point to die silently (currently it displays a big warning) if there are no entry.cmd files

## Modify entry point to not have the U.vbs mechanism for extra security, should be an option

# Seems cool, might have a use someday

## Permissions and icalcs

SIDS, security identifiers, added to ACLs, access control lists
permissions:
- https://www.howtogeek.com/72718/how-to-understand-those-confusing-windows-7-fileshare-permissions/
- https://www.online-tech-tips.com/computer-tips/set-file-folder-permissions-windows/
- https://www.dell.com/support/article/us/en/04/sln156352/understanding-file-and-folder-permissions-in-windows?lang=en

## Devcon, idk

## Networking

- net
- netstat
- ipconfig

## Physical devices

seems like batch can print stuff, like, actually sending signal to the printer