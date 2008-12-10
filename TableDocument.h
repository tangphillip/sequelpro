//
//  TableDocument.h
//  sequel-pro
//
//  Created by lorenz textor (lorenz@textor.ch) on Wed May 01 2002.
//  Copyright (c) 2002-2003 Lorenz Textor. All rights reserved.
//  
//  Forked by Abhi Beckert (abhibeckert.com) 2008-04-04
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//  More info at <http://code.google.com/p/sequel-pro/>

#import <Cocoa/Cocoa.h>
#import <MCPKit_bundled/MCPKit_bundled.h>
#import "CMMCPConnection.h"
#import "CMMCPResult.h"

/**
 * The TableDocument class controls the primary database view window.
 */

@interface TableDocument : NSDocument
{
  //IBOutlets
	IBOutlet id keyChainInstance;
	IBOutlet id tablesListInstance;
	IBOutlet id tableSourceInstance;
	IBOutlet id tableContentInstance;
	IBOutlet id customQueryInstance;
	IBOutlet id tableDumpInstance;
	IBOutlet id tableStatusInstance;

	IBOutlet id tableWindow;
	IBOutlet id connectSheet;
	IBOutlet id databaseSheet;
	IBOutlet id variablesSheet;
	IBOutlet id consoleDrawer;

	IBOutlet id queryProgressBar;
	IBOutlet id favoritesButton;
	IBOutlet NSTableView *connectFavoritesTableView;
	IBOutlet NSArrayController *favoritesController;
	IBOutlet id hostField;
	IBOutlet id socketField;
	IBOutlet id userField;
	IBOutlet id passwordField;
	IBOutlet id portField;
	IBOutlet id databaseField;

	IBOutlet id connectProgressBar;
	IBOutlet id connectProgressStatusText;
	IBOutlet id databaseNameField;
	IBOutlet id chooseDatabaseButton;
	IBOutlet id consoleTextView;
	IBOutlet id variablesTableView;
	IBOutlet NSTabView *tableTabView;
	
	IBOutlet id sidebarGrabber;
	
	IBOutlet NSTableView *dbTablesTableView;

	IBOutlet id syntaxView;
	IBOutlet id syntaxViewContent;
	IBOutlet NSWindow *createTableSyntaxWindow;

	CMMCPConnection *mySQLConnection;

	NSMutableArray *favorites;
	NSArray *variables;
	NSString *selectedDatabase;
	NSString *mySQLVersion;
	NSUserDefaults *prefs;

	NSMenu *selectEncodingMenu;
	BOOL _supportsEncoding;
	NSString *_encoding;

	NSToolbar *mainToolbar;
	NSToolbarItem *chooseDatabaseToolbarItem;
}

//start sheet
- (IBAction)connectToDB:(id)sender;
- (IBAction)connect:(id)sender;
- (IBAction)cancelConnectSheet:(id)sender;
- (IBAction)closeSheet:(id)sender;
- (IBAction)chooseFavorite:(id)sender;
- (IBAction)removeFavorite:(id)sender;
- (id)selectedFavorite;
- (NSString *)selectedFavoritePassword;
- (void)connectSheetAddToFavorites:(id)sender;
- (void)addToFavoritesHost:(NSString *)host socket:(NSString *)socket 
					  user:(NSString *)user password:(NSString *)password
					  port:(NSString *)port database:(NSString *)database
					useSSH:(BOOL)useSSH // no-longer in use
				   sshHost:(NSString *)sshHost // no-longer in use
				   sshUser:(NSString *)sshUser // no-longer in use
			   sshPassword:(NSString *)sshPassword // no-longer in use
				   sshPort:(NSString *)sshPort; // no-longer in use
- (NSMutableArray *)favorites;

//alert sheets method
- (void)sheetDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(NSString *)contextInfo;

//connection getter
- (CMMCPConnection *)sharedConnection;

//database methods
- (IBAction)setDatabases:(id)sender;
- (IBAction)chooseDatabase:(id)sender;
- (IBAction)addDatabase:(id)sender;
- (IBAction)closeDatabaseSheet:(id)sender;
- (IBAction)removeDatabase:(id)sender;

//console methods
- (void)toggleConsole:(id)sender;
- (void)clearConsole:(id)sender;
- (BOOL)consoleIsOpened;
- (void)showMessageInConsole:(NSString *)message;
- (void)showErrorInConsole:(NSString *)error;

//encoding methods
- (void)setEncoding:(NSString *)encoding;
- (void)detectDatabaseEncoding;
- (void)detectTableEncodingForTable:(NSString *)table;
- (IBAction)chooseEncoding:(id)sender;
- (BOOL)supportsEncoding;
- (void)updateEncodingMenuWithSelectedEncoding:(NSString *)encoding;
- (NSString *)encodingNameFromMySQLEncoding:(NSString *)mysqlEncoding;
- (NSString *)mysqlEncodingFromDisplayEncoding:(NSString *)encodingName;

//table methods
- (IBAction)showCreateTableSyntax:(id)sender;
- (IBAction)copyCreateTableSyntax:(id)sender;
- (IBAction)checkTable:(id)sender;
- (IBAction)analyzeTable:(id)sender;
- (IBAction)optimizeTable:(id)sender;
- (IBAction)repairTable:(id)sender;
- (IBAction)flushTable:(id)sender;
- (IBAction)checksumTable:(id)sender;

//other methods
- (NSString *)host;
- (void)doPerformQueryService:(NSString *)query;
- (void)flushPrivileges:(id)sender;
- (void)showVariables:(id)sender;
- (void)closeConnection;

//getter methods
- (NSString *)database;
- (NSString *)table;
- (NSString *)mySQLVersion;
- (NSString *)user;

//notification center methods
- (void)willPerformQuery:(NSNotification *)notification;
- (void)hasPerformedQuery:(NSNotification *)notification;
- (void)applicationWillTerminate:(NSNotification *)notification;
- (void)tunnelStatusChanged:(NSNotification *)notification;

//menu methods
- (BOOL)validateMenuItem:(NSMenuItem *)anItem;
- (IBAction)import:(id)sender;
- (IBAction)export:(id)sender;
- (IBAction)exportTable:(id)sender;
- (IBAction)exportMultipleTables:(id)sender;
- (IBAction)viewStructure:(id)sender;
- (IBAction)viewContent:(id)sender;
- (IBAction)viewQuery:(id)sender;
- (IBAction)viewStatus:(id)sender;

//toolbar methods
- (void)setupToolbar;
- (NSToolbarItem *)toolbar:(NSToolbar *)toolbar itemForItemIdentifier:(NSString *)itemIdentifier willBeInsertedIntoToolbar:(BOOL)flag;
- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar;
- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar*)toolbar;
- (BOOL)validateToolbarItem:(NSToolbarItem *)toolbarItem;
- (void)updateChooseDatabaseToolbarItemWidth;

//NSDocument methods
- (NSString *)windowNibName;
- (void)windowControllerDidLoadNib:(NSWindowController *)aController;
- (void)windowWillClose:(NSNotification *)aNotification;

//NSWindow delegate methods
- (BOOL)windowShouldClose:(id)sender;

//SMySQL delegate methods
- (void)willQueryString:(NSString *)query;
- (void)queryGaveError:(NSString *)error;

//splitView delegate methods
- (BOOL)splitView:(NSSplitView *)sender canCollapseSubview:(NSView *)subview;
- (float)splitView:(NSSplitView *)sender constrainMaxCoordinate:(float)proposedMax ofSubviewAt:(int)offset;
- (float)splitView:(NSSplitView *)sender constrainMinCoordinate:(float)proposedMin ofSubviewAt:(int)offset;
- (NSRect)splitView:(NSSplitView *)splitView additionalEffectiveRectOfDividerAtIndex:(int)dividerIndex;


//tableView datasource methods
- (int)numberOfRowsInTableView:(NSTableView *)aTableView;
- (id)tableView:(NSTableView *)aTableView
			objectValueForTableColumn:(NSTableColumn *)aTableColumn
			row:(int)rowIndex;

@end

extern NSString *TableDocumentFavoritesControllerSelectionIndexDidChange;
extern NSString *TableDocumentFavoritesControllerFavoritesDidChange;
