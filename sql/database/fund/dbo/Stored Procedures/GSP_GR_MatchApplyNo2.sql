

----------------------------------------------------------------------------------------------------
/*
EXEC GSP_GR_MatchApplyNo2 3,1010000,-10,-10,501,1150,501115001397725887,'127.0.0.1'



Declare @Ret int
Declare @Retmessage bigint
EXEC GSP_GR_MatchApplyNo2 1,1010000,10,10,501,1150,501115001397725887,'127.0.0.1',@Retmessage OUT ,@Ret OUT
SELECT @Ret,@Retmessage

Declare @Ret int
Declare @Retmessage bigint
EXEC GSP_GR_MatchApplyNo2 1,9662775,-16,0,520,0,37,'127.0.0.1',@Retmessage OUT ,@Ret OUT
SELECT @Ret,@Retmessage

SELECT * FROM QPTreasureDB.DBO.RecordGameScoreDetails WHERE USERID=1010000 ORDER BY ADDdATE ASC
SELECT * FROM QPGameUserDB.DBO.T_RegistrationRecord
SELECT * FROM QPTreasureDB.dbo.T_UserGold WHERE USERID=1010000
26641
DELETE QPTreasureDB.DBO.RecordGameScoreDetails WHERE USERID=1010000
DELETE FROM QPGameUserDB.DBO.T_RegistrationRecord
*/
-- 报名信息
create PROC [dbo].[GSP_GR_MatchApplyNo2]
    @TYPE INT,  --1=只扣返报名费 2=只扣返参赛券 3=报名费和参赛券同时扣返
	@dwUserID INT ,           --用户ID
	@lGold INT,				--金币	    
	@lMatchProve INT,		--参赛卷
	@wKindID INT,								-- 游戏 I D
	@wServerID INT,								-- 房间 I D
    @ScreeningsID bigint,						--场次ID
	@strClientIP VARCHAR(15),			-- 连接地址
	@Retmessage bigint output,
	@Ret int output
AS
SET NOCOUNT ON -- 属性设置
DECLARE @OldMatchProve INT
DECLARE @OldGold BIGINT

DECLARE @Res INT
DECLARE @FLAG INT
DECLARE @Retmess varchar(50)
-- 执行逻辑
BEGIN    
    IF @TYPE=1       --1=只扣返报名费
       BEGIN
			  Declare @CollectNote varchar(50) ,@LastScore BIGINT,@Returnprm varchar(32)
			  SET @lMatchProve=0
			  SET @OldGold=@lGold
			  IF @lGold<0
					BEGIN
						--更新用户数据
							SET @CollectNote ='比赛报名费扣币'+cast(@lGold AS NVARCHAR(32))+'。'
							SET @lGold=ABS(@lGold)
							Exec QPTreasureDBLink.QPTreasureDB.dbo.GSP_Common_AccountScoreChange 0,31,@dwUserID,0,0,@lMatchProve,@lGold,@wKindID,@wServerID,@CollectNote,@TYPE,@OldGold,@ScreeningsID,@strClientIP,@Returnprm out,@Ret out,@Retmess out
							IF @Ret=1
								  BEGIN
									 EXEC QPTreasureDBLink.QPGameUserDB.DBO.Proc_RegistrationRecord 1,1,@dwUserID,@wKindID,@wServerID,@ScreeningsID,@OldGold,@lMatchProve,@strClientIP,@Returnprm,@CollectNote,@TYPE,NULL
									 EXEC QPTreasureDBLink.QPTreasureDB.dbo.Proc_UpdateMatchScreenings @ScreeningsID,@wKindID,@wServerID,1
									 set @Retmessage = @Retmess;
								  END
							SELECT @Retmess AS [ErrorDescribe]						     
							
							RETURN
					END
				ELSE IF @lGold>0
					BEGIN
					    SET @CollectNote ='用户主动退赛返还比赛报名费'+cast(@lGold AS NVARCHAR(32))+'。'
					    EXEC QPTreasureDBLink.QPGameUserDB.DBO.Proc_RegistrationRecord 1,0,@dwUserID,@wKindID,@wServerID,@ScreeningsID,@lGold,@lMatchProve,@strClientIP,@Returnprm,@CollectNote,@TYPE,@FLAG OUTPUT
					    IF @FLAG=1
					       BEGIN		     					
								Exec QPTreasureDBLink.QPTreasureDB.dbo.GSP_Common_AccountScoreChange 1,31,@dwUserID,0,0,@lMatchProve,@lGold,@wKindID,@wServerID,@CollectNote,@TYPE,@lGold,@ScreeningsID,@strClientIP,@Returnprm out,@Ret out,@Retmess out
								IF @Ret=1
									BEGIN
										EXEC QPTreasureDBLink.QPTreasureDB.dbo.Proc_UpdateMatchScreenings @ScreeningsID,@wKindID,@wServerID,0
										set @Retmessage = @Retmess;
							        END
							    SELECT @Retmess AS [ErrorDescribe]
							    --SELECT @Ret AS Result
							    
								RETURN
						   END
						ELSE
						   BEGIN
						      SELECT [ErrorDescribe]=N'返还报名费失败，请于客服联系！'
						   
							  RETURN 3
						   END					
					END
				ELSE
					 BEGIN
						SELECT [ErrorDescribe]=N'比赛报名失败(报名费)，请与客服联系！'
						RETURN 3
					 END
       END
    ELSE IF @TYPE=2  --2=只扣返参赛券
       BEGIN           
           SET @lGold=0
           EXEC QPTreasureDBLink.QPGameUserDB.dbo.Proc_GameGoldEgg @dwUserID,NULL,@OldMatchProve OUT
           IF @lMatchProve<0   --报名扣参赛券
				BEGIN
				  IF @OldMatchProve>=-1*@lMatchProve
					BEGIN
					   EXEC  QPTreasureDBLink.QPGameUserDB.dbo.Proc_GameGoldEggUpdate @dwUserID,1,@lMatchProve, @Res OUT
						   IF @Res=1
								 BEGIN
									   SET @CollectNote ='比赛报名扣参赛券'+cast(ABS(@lMatchProve) AS NVARCHAR(32))+'。'					   
									   Exec QPTreasureDBLink.QPTreasureDB.dbo.GSP_Common_AccountScoreChange 0,32,@dwUserID,0,0,@lMatchProve,0,@wKindID,@wServerID,@CollectNote,@TYPE,@lMatchProve,@ScreeningsID,@strClientIP,@Returnprm out,@Ret out,@Retmess out
									   IF @Ret=1
											  BEGIN
												 EXEC QPTreasureDBLink.QPGameUserDB.DBO.Proc_RegistrationRecord 0,1,@dwUserID,@wKindID,@wServerID,@ScreeningsID,@lGold,@lMatchProve,@strClientIP,@Returnprm,@CollectNote,@TYPE,NULL
											     EXEC QPTreasureDBLink.QPTreasureDB.dbo.Proc_UpdateMatchScreenings @ScreeningsID,@wKindID,@wServerID,1
												 set @Retmessage = @Retmess;
											  END									   
									   SELECT @Retmess AS [ErrorDescribe]
									   RETURN						    
								 END
						   ELSE
								 BEGIN
									SELECT [ErrorDescribe]=N'报名扣费失败！'
									RETURN 2
								 END
					END
				  ELSE
					BEGIN
						   SELECT [ErrorDescribe]=N'您当前没有足够报名所需的参赛券数量，继续努力吧！'
						   RETURN 2
					END
				END
			ELSE IF @lMatchProve>0 --返还参赛券
			   BEGIN
					EXEC  QPTreasureDBLink.QPGameUserDB.dbo.Proc_GameGoldEggUpdate @dwUserID,1,@lMatchProve,@Res OUT
					IF @Res=1
							 BEGIN
								SET @CollectNote ='用户主动退赛返还比赛参赛券'+cast(@lMatchProve AS NVARCHAR(32))+'。'	
								EXEC QPTreasureDBLink.QPGameUserDB.DBO.Proc_RegistrationRecord 0,0,@dwUserID,@wKindID,@wServerID,@ScreeningsID,@lGold,@lMatchProve,@strClientIP,@Returnprm,@CollectNote,@TYPE,@FLAG OUTPUT							
								IF @FLAG=1
								   BEGIN
										Exec QPTreasureDBLink.QPTreasureDB.dbo.GSP_Common_AccountScoreChange 1,32,@dwUserID,0,0,@lMatchProve,0,@wKindID,@wServerID,@CollectNote,@TYPE,@lMatchProve,@ScreeningsID,@strClientIP,@Returnprm out,@Ret out,@Retmess out
										IF @Ret=1
										   BEGIN
												EXEC QPTreasureDBLink.QPTreasureDB.dbo.Proc_UpdateMatchScreenings @ScreeningsID,@wKindID,@wServerID,0
												set @Retmessage = @Retmess;
									       END
										SELECT  @Retmess AS [ErrorDescribe]
										RETURN
								   END
								ELSE
								   BEGIN								   
								       SELECT [ErrorDescribe]=N'返还比赛参赛券失败，请于客服联系！'
								       RETURN 2
								   END								
							 END
					ELSE
					     BEGIN
								SELECT [ErrorDescribe]=N'报名扣比赛参赛券失败！'
								RETURN 2
					     END
			   END 
			ELSE
			   BEGIN
					 SELECT [ErrorDescribe]=N'比赛报名失败(参赛券)，请与客服联系！'
					 RETURN 5
			   END          
       END
    ELSE IF @TYPE=3  --3=报名费和参赛券同时扣返
            BEGIN 
            IF  (@lMatchProve<0 AND @lGold>=0) OR(@lMatchProve>0 AND @lGold<=0) OR (@lGold>0 AND @lMatchProve<=0) OR (@lGold<0 AND @lMatchProve>=0)
                BEGIN
					   SELECT [ErrorDescribe]=N'比赛报名参数异常，报名失败！'
					   RETURN 5
                END             
            IF  @lMatchProve<>0 AND @lGold<>0   
                BEGIN   
					   EXEC QPTreasureDBLink.QPGameUserDB.dbo.Proc_GameGoldEgg @dwUserID,NULL,@OldMatchProve OUT
					   IF @lMatchProve<0   --报名扣参赛券
						BEGIN
						  IF @OldMatchProve>=-1*@lMatchProve
							BEGIN
							   EXEC  QPTreasureDBLink.QPGameUserDB.dbo.Proc_GameGoldEggUpdate @dwUserID,1,@lMatchProve,@Res OUT
							   IF @Res=1
									BEGIN
										   SET @CollectNote ='比赛扣除报名费'+cast(ABS(@lGold) AS NVARCHAR(32))+'个币，参赛券'+cast(ABS(@lMatchProve) AS NVARCHAR(32))+'张。'
										   SET @OldGold=ABS(@lGold)
										   Exec QPTreasureDB.dbo.GSP_Common_AccountScoreChange 0,33,@dwUserID,0,0,@lMatchProve,@OldGold,@wKindID,@wServerID,@CollectNote,@TYPE,@lMatchProve,@ScreeningsID,@strClientIP,@Returnprm out,@Ret out,@Retmess out
										   IF @Ret=1
												  BEGIN
													 EXEC QPTreasureDBLink.QPGameUserDB.DBO.Proc_RegistrationRecord 1,1,@dwUserID,@wKindID,@wServerID,@ScreeningsID,@lGold,@lMatchProve,@strClientIP,@Returnprm,@CollectNote,@TYPE,NULL
												     EXEC QPTreasureDBLink.QPTreasureDB.dbo.Proc_UpdateMatchScreenings @ScreeningsID,@wKindID,@wServerID,1
													 set @Retmessage = @Retmess;
												  END											
									 	   SELECT  @Retmess AS [ErrorDescribe]
									 	   RETURN
									 END
								ELSE
									 BEGIN
										SELECT [ErrorDescribe]=N'报名扣费失败！'
										RETURN 2
									 END
							 END
						  ELSE
								BEGIN
								   SELECT [ErrorDescribe]=N'您当前没有足够报名所需的参赛券数量，继续努力吧！'
								   RETURN 2
								END
						END
					ELSE IF @lMatchProve>0 --返还扣参赛券
					   BEGIN
							EXEC  QPTreasureDBLink.QPGameUserDB.dbo.Proc_GameGoldEggUpdate @dwUserID,1,@lMatchProve,@Res OUT
							IF @Res=1
								 BEGIN
										SET @CollectNote ='用户主动退赛返还报名费'+cast(@lGold AS NVARCHAR(32))+'个币，参赛券'+cast(@lMatchProve AS NVARCHAR(32))+'张。'
										EXEC QPTreasureDBLink.QPGameUserDB.DBO.Proc_RegistrationRecord 1,0,@dwUserID,@wKindID,@wServerID,@ScreeningsID,@lGold,@lMatchProve,@strClientIP,@Returnprm,@CollectNote,@TYPE,@FLAG OUTPUT
										IF @FLAG=1
										   BEGIN 
												Exec QPTreasureDBLink.QPTreasureDB.dbo.GSP_Common_AccountScoreChange 1,33,@dwUserID,0,0,@lMatchProve,@lGold,@wKindID,@wServerID,@CollectNote,@TYPE,@lMatchProve,@ScreeningsID,@strClientIP,@Returnprm out,@Ret out,@Retmess out
												IF @Ret=1
												    BEGIN
												       EXEC QPTreasureDBLink.QPTreasureDB.dbo.Proc_UpdateMatchScreenings @ScreeningsID,@wKindID,@wServerID,0
													   set @Retmessage = @Retmess;
													END
										   									    
												SELECT @Retmess AS [ErrorDescribe]
												RETURN
											END
									   ELSE
									      BEGIN									          
									          SELECT [ErrorDescribe]=N'返还报名费和比赛券失败，请联系客服！'
											  RETURN 2
									      END
							     END
							ELSE
								 BEGIN
										SELECT [ErrorDescribe]=N'报名扣报名费和比赛券失败！'
										RETURN 2
								 END
					   END
					ELSE IF @lMatchProve=0 OR @lGold<=0
					   BEGIN
							  SELECT [ErrorDescribe]=N'您当前没有足够报名所需的参赛券或没有足够支付报名所需的报名费，继续努力吧！'
							  RETURN 2
					   END 
			    END
			 ELSE
			    BEGIN
					   SELECT [ErrorDescribe]=N'比赛报名失败(参赛券或报名费)，请与客服联系！'
					   RETURN 5
			    END        
            END     
END