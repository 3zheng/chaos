
/*
Declare  @Returnprm BIGINT
Declare  @Retmessage BIGINT
Declare  @Ret INT
EXEC GSP_GR_WriteGameGold 1010000,1000,501,1300,18,'127.0.0.1',10,11,201407295011301,@Returnprm OUT,@Retmessage OUT,@Ret OUT
SELECT @Returnprm,@Retmessage,@Ret
165	25821	1
--SELECT * FROM T_GameScoreRecord WHERE USERID=1010000 ORDER BY ADDDATE
SELECT * FROM QPTreasureDBLink.QPTreasureDB.dbo.T_UserGold WHERE USERID=1010000
SELECT * FROM QPTreasureDBLink.QPTreasureDB.dbo.RecordGameScoreDetails WHERE USERID=1010000

*/
create PROC [dbo].[GSP_GR_WriteGameGold]
	@dwUserID INT,
	@lSwapScore BIGINT,
	@dwKindID INT,
	@dwServerID INT,
	@wTradeType INT,
	@strClientIP NVARCHAR(15),
	@GoldEgg INT,
	@MatchProve INT,
	@ScreeningsID BIGINT,
	@Returnprm BIGINT output, /*输出备用*/
	@Retmessage BIGINT output, /*成功返回操作后余额，失败则返回失败信息*/
	@Ret int output
AS
-- 属性设置
SET NOCOUNT ON
-- 执行逻辑
BEGIN
		 Declare @CollectNote varchar(50) ,@LastScore BIGINT, @Retmess varchar(50), @Retprm varchar(50) --,@Score BIGINT
	     --exec QPTreasureDB.dbo.Proc_GameUserGold @dwUserID,@Score out,null,null,null
		--更新用户数据		
     	 
         SET @LastScore=0--@lSwapScore+@Score
	     SET @CollectNote ='比赛场胜利奖励金币:'+cast(@lSwapScore AS VARCHAR(32))+' 奖券:'+cast(@GoldEgg AS VARCHAR(32))
	     Exec QPTreasureDBLink.QPTreasureDB.dbo.GSP_Common_AccountScoreChange  1,29,@dwUserID,0,@wTradeType,@GoldEgg,@lSwapScore,@dwKindID,@dwServerID,@CollectNote,null,null,@ScreeningsID,@strClientIP,@Retprm out,@Ret out,@Retmess out
         IF @Ret=1
            BEGIN
			   set @Returnprm = @Retprm;
               set @Retmessage = @Retmess;
            END         
END