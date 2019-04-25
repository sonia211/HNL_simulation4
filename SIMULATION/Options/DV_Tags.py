from DB import decays_db

#dictionary for all the tags
MC_tags = {"16" : {	    "DDDB"	:	"dddb-20150724",
			    "CONDDB" 	:	"sim-20161124-2-vc-{0}100"
		    },
	    "11" : {        "DDDB"	:	"dddb-20130929-1",
			    "CONDDB" 	:	"sim-20130522-1-vc-{0}100"
		    },
	    "12" : {	
			    "DDDB"		:	"dddb-20130929-1",
			    "CONDDB" 	:	"sim-20130522-1-vc-{0}100"
		    },
	    "15" : {
			    "DDDB"		:	"dddb-20130929-1",
			    "CONDDB" 	:	"sim-20130522-1-vc-{0}100"
		    },


	    }


def get_MC_tag (decay = '', year = '', magPol = '', tag = ''):
	try:
                
                tag = decays_db[decay][tag.lower()][year].format(magPol.lower())
		#tag = MC_tags[year][magPol][tag]
		return tag
	except:
		print "Error! Tag not found! Is the year, the polarity or the requested tag not existing?"
                print "Decay =",decay
                print "Year  =",year
                print "Mag   =",magPol.lower()
                print "Tag   =",tag.lower()
		return None
