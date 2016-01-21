//N
A[1] = 	genAtom("IDNTER", 0, NonTerminal);

//T
A[3] =	genConc(
			genAtom("F", 0, NonTerminal),
				genStar(
					genConc(
						genAtom(".", 0, Terminal),
						genAtom("F", 0, NonTerminal)
					)
				)
		);
		
A[4] = genUnion(
			genUnion(
				genAtom("IDNTER", 0, NonTerminal),
				genAtom("ELTER", 0, Terminal)
			),
			genUnion(
				genUnion(
					genConc(
						genAtom("(", 0, Terminal),
						genConc(
							genAtom("E", 0, NonTerminal),
							genAtom(")", 0, Terminal)
						)
						
					),
					
				),
				
			)
		)
