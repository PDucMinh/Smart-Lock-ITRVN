# Domain Context
Nowadays, Smart Door Locks are integrated completely in many apartments due to the convenience and the safety brought to people by it. Each household doesn’t need to use the manual locks which is bulky and vulnerable. Traditional lock is broken easily by mechanical tools, whereas the smart lock hide its actuator for locking inside the door and therefor, it’s hard to pry open the door. Manual lock always needs to go together with a key, that will lead to the risk of losing and we must keep a spare one somewhere else, which make the manual lock even more unfavorable. Smart lock offer more advantageous options which will be described in bellow.

# Detailed features

## Functional Requirement

The Smart Door Locks will provide all the following features:
- The Lock operates in two modes, RFID mode and Password mode. In RFID mode, the lock will open if it sense the correct tag. In Password mode, the lock will open when user enter the right password. User can choose either method to open the door.
- The Lock allows user to set up new password. It will become valid right after the setting complete. The Lock also support user with setting up new RFID card in case the old one is lost.
- The Lock provides user hierarchy include two levels of user which are admin and household. Admin’s rights consist of accessing to logging information, accessing to household information, opening the door independent of household’s password, setting up new household’s information. Household’s rights include opening the door with password or RFID tag, setting up new password, setting up new RFID.

## Non-functional Requirement

- The length of user's password is at least 8 characters which is then encrypted in bencode.
- The Lock can detect the state of the door is locked or opened. If it is left opened for more than 5 seconds, the lock will automatically enter locked state.
- The logging mechanism of the lock will store the information of accessing time, the state of the Lock, the user accessing the lock at the time the user presents RFID tag or enters password.
- The Lock log the information starting from 20 days before present day. After each day, the system will delete the information on the oldest day.
- 